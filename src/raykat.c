#include "raykat.h"

#include <X11/Xlib.h>
#include <stdio.h>
#include <time.h>

#include "output.h"
#include "camera.h"
#include "scene.h"

#define IMG_HEIGHT 720
#define IMG_WIDTH 1080
#define ASPECT_RATIO ((double) IMG_HEIGHT / (double) IMG_WIDTH)
#define TOTAL_PIXELS (IMG_WIDTH * IMG_HEIGHT)
#define SAMPLES_PER_PIXEL 100
#define MAX_DEPTH 50

/* ANSI colored output */
#define YELLOW "\e[0;33m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define RESETCOL "\e[0m"

color3 ray_color(ray* r, hittable_list* world, int depth) {
	hit_record rec;

	color3 black = {{ 0, 0, 0 }};
	if (depth <= 0) return black; // Recursion guard: return black if we've exceeded the bounce limit

	/* If object is hit */
	if (hittable_list_hit(world, r, 0.001, INFINITY, &rec)) {
		vec3 temp0 = vec3_add(&rec.p, &rec.normal);
		vec3 temp1 = vec3_random_unit_vector();
		//vec3 temp1 = vec3_random_in_hemisphere(&rec.normal);
		point3 target = vec3_add(&temp0, &temp1);

		ray temp2 = { rec.p, vec3_sub(&target, &rec.p) };
		color3 temp3 = ray_color(&temp2, world, depth - 1);
		return vec3_multiply_double(&temp3, 0.5);
	}

	/* Background lerp */
	vec3 unit_direction = vec3_norm(&r->direction);
	double hit = 0.5 * (unit_direction.y + 1.0);

	color3 temp0 = {{ 1.0, 1.0, 1.0 }};
	color3 temp1 = {{ 0.5, 0.7, 1.0 }};
	color3 prod0 = vec3_multiply_double(&temp0, 1.0 - hit);
	color3 prod1 = vec3_multiply_double(&temp1, hit);
	/* blendedValue = (1 - hit) * startValue + hit * endValue */
	return vec3_add(&prod0, &prod1);
}

int main() {
	/* WORLD */
	hittable_list* world = create_scene(SCENE_SPHERES);

	/* CAMERA */
	point3 lookfrom = {{ 3.5, 3, 1 }};
	point3 lookat = {{ 0, -1, 0 }};
	vec3 vup = {{ 0, 0, 1 }};
	double aperture = 0.1;
	vec3 temp0 = vec3_sub(&lookfrom, &lookat);
	double dist_to_focus = vec3_length(&temp0);
	//double dist_to_focus = 7.0;
	camera cam = camera_init(&lookfrom, &lookat, &vup, 20.0, ASPECT_RATIO, aperture, dist_to_focus);

	/* RENDER */
	pixel pixel_arr[TOTAL_PIXELS];

	clock_t start = clock();

	printf("P3\n%d %d\n255\n", IMG_WIDTH, (int)IMG_HEIGHT); /* PPM header:
							      P3 means colors are in ascii
							      followed by width and height */

	for (unsigned int i = 0; i < TOTAL_PIXELS; ++i) {
		pixel_arr[i].x = i % IMG_WIDTH;
		pixel_arr[i].y = i / IMG_WIDTH;

		color3 bg_color = {{ HEX_TO_RGB(PREVIEW_BG) }};
		//pixel_arr[i].color_rgb = bg_color;
		//pixel_arr[i].color_hex = PREVIEW_BG;

		//pixel_arr[i].rendered = false;
	}

	for (int i = IMG_HEIGHT - 1; i >= 0; --i) {
		for (int j = 0; j < IMG_WIDTH; ++j) {
			color3 pixel_color = {{ HEX_TO_RGB(PREVIEW_BG) }};

			write_color_to_file(stdout, &pixel_color, SAMPLES_PER_PIXEL);
		}
	}

	// TODO(ktkk): Surround this loop with the window loop. Or find a different solution.
	//for (int i = IMG_HEIGHT - 1; i >= 0; --i) {
	//	fprintf(stderr, YELLOW "\rScanlines remaining: " RED "%3d" RESETCOL, i);
	//	fflush(stderr);

	//	for (int j = 0; j < IMG_WIDTH; ++j) {
	//		color3 pixel_color = {{ 0, 0, 0 }};

	//		for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
	//			double u = (j + RAND_DOUBLE) / (IMG_WIDTH - 1);
	//			double v = (i + RAND_DOUBLE) / (IMG_HEIGHT - 1);

	//			ray r = camera_get_ray(&cam, u, v);
	//			color3 raycolor = ray_color(&r, world, MAX_DEPTH);
	//			pixel_color = vec3_add(&pixel_color, &raycolor);
	//		}

	//		write_color_to_file(stdout, &pixel_color, SAMPLES_PER_PIXEL);
	//	}
	//}

	clock_t diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;

	fprintf(stderr, GREEN "\nDone.\n" RESETCOL "Took %d seconds and %d milliseconds.\n", msec / 1000, msec % 1000);

	cleanup_scene(world);
}
