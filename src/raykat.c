#include "raykat.h"

#include <stdio.h>

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#define ASPECT_RATIO (16.0/9.0)
#define IMG_WIDTH 400
#define IMG_HEIGHT (int)(IMG_WIDTH / ASPECT_RATIO)
#define SAMPLES_PER_PIXEL 100
#define MAX_DEPTH 50

/* Test function that produces a gradient value for a given ray */
color3 ray_color(ray* r, hittable_list* world, int depth) {
	hit_record rec;

	color3 black = {{ 0, 0, 0 }};
	if (depth <= 0) return black; // Recursion guard: return black if we've exceeded the bounce limit

	if (hittable_list_hit(world, r, 0, INFINITY, &rec)) {
		vec3 temp0 = vec3_add(&rec.p, &rec.normal);
		vec3 temp1 = vec3_random_in_unit_sphere();
		point3 target = vec3_add(&temp0, &temp1);

		ray temp2 = { rec.p, vec3_sub(&target, &rec.p) };
		color3 temp3 = ray_color(&temp2, world, depth - 1);
		return vec3_multiply_double(&temp3, 0.5);
	}

	vec3 unit_direction = vec3_norm(&r->direction);
	double hit = 0.5 * (unit_direction.y + 1.0);

	color3 temp0 = {{ 1.0, 1.0, 1.0 }};
	color3 temp1 = {{ 0.5, 0.7, 1.0 }};
	color3 prod0 = vec3_multiply_double(&temp0, 1.0 - hit);
	color3 prod1 = vec3_multiply_double(&temp1, hit);
	/* blendedValue = (1 - t) * startValue + t * endValue */
	return vec3_add(&prod0, &prod1);
}

int main() {
	/* WORLD */
	hittable_list world = hittable_list_init(2);
	point3 center0 = {{ 0, 0, -1 }};
	point3 center1 = {{ 0, -100.5, -1 }};
	hittable_list_add(&world, sphere_new(&center0, 0.5));
	hittable_list_add(&world, sphere_new(&center1, 100));

	/* CAMERA */
	camera cam = camera_init();

	/* RENDER */
	printf("P3\n%d %d\n255\n", IMG_WIDTH, IMG_HEIGHT); /* PPM header:
							      P3 means colors are in ascii
							      followed by width and height */
	for (int i = IMG_HEIGHT - 1; i >= 0; --i) {
		fprintf(stderr, "\rScanlines remaining: %03d", i);
		fflush(stderr);

		for (int j = 0; j < IMG_WIDTH; ++j) {
			color3 pixel_color = {{ 0, 0, 0 }};

			for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
				double u = (j + RAND_DOUBLE) / (IMG_WIDTH - 1);
				double v = (i + RAND_DOUBLE) / (IMG_HEIGHT - 1);

				ray r = camera_get_ray(&cam, u, v);
				color3 raycolor = ray_color(&r, &world, MAX_DEPTH);
				pixel_color = vec3_add(&pixel_color, &raycolor);
			}

			write_color(stdout, &pixel_color, SAMPLES_PER_PIXEL);
		}
	}

	fprintf(stderr, "\nDone.\n");
}
