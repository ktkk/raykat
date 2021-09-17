#include <stdio.h>

#include "vec3.h"
#include "color.h"
#include "ray.h"

#define ASPECT_RATIO (16.0/9.0)
#define IMG_WIDTH 400
#define IMG_HEIGHT (int)(IMG_WIDTH / ASPECT_RATIO)

#define VIEW_HEIGHT 2.0
#define VIEW_WIDTH ASPECT_RATIO * VIEW_HEIGHT
#define FOCAL_LENGTH 1.0

/* Test function that produces a gradient value for a given ray */
color3 bg_color(ray* r) {
	vec3 unit_direction = vec3_norm(&r->direction);
	double t = 0.5 * (unit_direction.y + 1.0);

	color3 temp0 = {{ 1.0, 1.0, 1.0 }};
	color3 temp1 = {{ 0.5, 0.7, 1.0 }};
	color3 prod0 = vec3_multiply_double(&temp0, 1.0 - t);
	color3 prod1 = vec3_multiply_double(&temp1, t);
	return vec3_add(&prod0, &prod1);
}

int main() {
	/* CAMERA */
	point3 origin = {{ 0, 0, 0 }};
	vec3 horizontal = {{ VIEW_WIDTH, 0, 0 }};
	vec3 vertical = {{ 0, VIEW_HEIGHT, 0 }};

	point3 half_hor = vec3_divide(&horizontal, 2);
	point3 half_vert = vec3_divide(&vertical, 2);
	point3 temp0 = vec3_sub(&origin, &half_hor);
	point3 temp1 = vec3_sub(&temp0, &half_vert);
	point3 temp2 = {{ 0, 0, FOCAL_LENGTH }};
	point3 lower_left_corner = vec3_sub(&temp1, &temp2);

	/* RENDER */
	printf("P3\n%d %d\n255\n", IMG_WIDTH, IMG_HEIGHT); /* PPM header:
							      P3 means colors are in ascii
							      followed by width and height */
	for (int i = IMG_HEIGHT - 1; i >= 0; --i) {
		fprintf(stderr, "\rScanlines remaining: %d", i);
		fflush(stderr);

		for (int j = 0; j < IMG_WIDTH; ++j) {
			double u = (double)j / (IMG_WIDTH - 1);
			double v = (double)i / (IMG_HEIGHT - 1);

			point3 h_pos = vec3_multiply_double(&horizontal, u);
			point3 v_pos = vec3_multiply_double(&vertical, v);
			temp0 = vec3_add(&lower_left_corner, &h_pos);
			temp1 = vec3_add(&temp0, &v_pos);
			point3 direction = vec3_sub(&temp1, &origin);

			ray r = { origin, direction };
			color3 pixel_color = bg_color(&r);

			write_color(stdout, &pixel_color);
		}
	}

	fprintf(stderr, "\nDone.\n");
}
