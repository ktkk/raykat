#include "raykat.h"

#include <stdio.h>
#include <time.h>
#include <math.h>

#include "camera.h"
#include "scene.h"
#include "material.h"

#include "vec3.h"

#define ASPECT_RATIO (3.0 / 2.0)
#define IMG_WIDTH 1200
#define IMG_HEIGHT (int)(IMG_WIDTH / ASPECT_RATIO)
#define SAMPLES_PER_PIXEL 500
#define MAX_DEPTH 50

/* ANSI colored output */
#define YELLOW "\e[0;33m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define RESETCOL "\e[0m"

static color3 ray_color(const ray* r, const hittable_list* world, const int depth);
static inline void write_color(FILE* stream, const color3* color, const unsigned int samples_per_pixel);

int main() {
	/* WORLD */
	hittable_list* world = create_scene(SCENE_RANDOM);

	/* CAMERA */
	const point3 lookfrom = {{ 13, 2, 3 }};
	const point3 lookat = {{ 0, 0, 0 }};
	const vec3 vup = {{ 0, 1, 0 }};
	const double aperture = 0.1;
	const double dist_to_focus = 10.0;
	const camera cam = camera_init(&lookfrom, &lookat, &vup, 20.0, ASPECT_RATIO, aperture, dist_to_focus);

	/* RENDER */
	const clock_t start = clock();

	printf("P3\n%d %d\n255\n", IMG_WIDTH, IMG_HEIGHT); /* PPM header:
							      P3 means colors are in ascii
							      followed by width and height */

	for (int i = IMG_HEIGHT - 1; i >= 0; --i) {
		fprintf(stderr, YELLOW "\rScanlines remaining: " RED "%3d" RESETCOL, i);
		fflush(stderr);

		for (int j = 0; j < IMG_WIDTH; ++j) {
			color3 pixel_color = {{ 0, 0, 0 }};

			for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
				const double u = (j + RAND_DOUBLE) / (IMG_WIDTH - 1);
				const double v = (i + RAND_DOUBLE) / (IMG_HEIGHT - 1);

				const ray r = camera_get_ray(&cam, u, v);
				color3 raycolor = ray_color(&r, world, MAX_DEPTH);
				pixel_color = vec3_add(&pixel_color, &raycolor);
			}

			write_color(stdout, &pixel_color, SAMPLES_PER_PIXEL);
		}
	}

	const clock_t diff = clock() - start;
	const int msec = diff * 1000 / CLOCKS_PER_SEC;

	fprintf(stderr, GREEN "\nDone.\n" RESETCOL "Took %d seconds and %d milliseconds.\n", msec / 1000, msec % 1000);

	cleanup_scene(world);
}

static inline void write_color(FILE* stream, const color3* color, const unsigned int samples_per_pixel) {
	const double scale = 1.0 / samples_per_pixel;
	const double r = sqrt(scale * color->r);
	const double g = sqrt(scale * color->g);
	const double b = sqrt(scale * color->b);

#define CONVERT_COMPONENT(name) (int)(255.999 * name)

	/* Write out the translated [0, 255] value of each color component */
	fprintf(stream, "%d %d %d\n",
			CONVERT_COMPONENT(clamp(r, 0.0, 0.999)),
			CONVERT_COMPONENT(clamp(g, 0.0, 0.999)),
			CONVERT_COMPONENT(clamp(b, 0.0, 0.999))
		);
}

static color3 ray_color(const ray* r, const hittable_list* world, const int depth) {
	hit_record rec;

	const color3 black = {{ 0, 0, 0 }};
	if (depth <= 0) return black; // Recursion guard: return black if we've exceeded the bounce limit

	/* Color is determined by either the ray bouncing between surfaces endlessly until the recursion guard is hit,
	 * creating shadow, or it hitting the background. */

	/* If object is hit */
	if (hittable_list_hit(world, r, 0.001, INFINITY, &rec)) {
		ray scattered = { .origin = {{ 0, 0, 0 }}, .direction = {{ 0, 0, 0 }} };
		color3 attenuation = {{ 0, 0, 0 }};

		if (material_scatter(rec.mat_ptr, r, &rec, &attenuation, &scattered)) {
			color3 temp0 = ray_color(&scattered, world, depth - 1);

			return vec3_multiply_vectors(&attenuation, &temp0);
		}

		return black;
	}

	/* Background lerp */
	const vec3 unit_direction = vec3_norm(&r->direction);
	const double hit = 0.5 * (unit_direction.y + 1.0);

	const color3 temp0 = {{ 1.0, 1.0, 1.0 }};
	const color3 temp1 = {{ 0.5, 0.7, 1.0 }};
	const color3 prod0 = vec3_multiply_double(&temp0, 1.0 - hit);
	const color3 prod1 = vec3_multiply_double(&temp1, hit);
	/* blendedValue = (1 - hit) * startValue + hit * endValue */
	return vec3_add(&prod0, &prod1);
}
