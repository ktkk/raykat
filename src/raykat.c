#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "vec3.h"
#include "color.h"
#include "ray.h"

#define ASPECT_RATIO (16.0/9.0)
#define IMG_WIDTH 400
#define IMG_HEIGHT (int)(IMG_WIDTH / ASPECT_RATIO)

#define VIEW_HEIGHT 2.0
#define VIEW_WIDTH ASPECT_RATIO * VIEW_HEIGHT
#define FOCAL_LENGTH 1.0

double hit_sphere(point3* center, double radius, ray* r) {
	vec3 oc = vec3_sub(&r->origin, center);
	double a = vec3_length_squared(&r->direction);
	double half_b = vec3_dotprod(&oc, &r->direction);
	double c = vec3_length_squared(&oc) - radius * radius;
	double discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return -1.0;
	else
		return (-half_b - sqrt(discriminant)) / a;
}

/* Test function that produces a gradient value for a given ray */
color3 ray_color(ray* r) {
	point3 sphere_center = {{ 0, 0, -1 }};
	double sphere_radius = 0.5;
	double hit = hit_sphere(&sphere_center, sphere_radius, r);
	if (hit > 0.0) {
		point3 temp0 = ray_at(r, hit);
		point3 temp1 = {{ 0, 0, -1 }};
		point3 temp2 = vec3_sub(&temp0, &temp1);
		vec3 n = vec3_norm(&temp2);

		color3 temp3 = {{ 0.5 * (n.x + 1), 0.5 * (n.y + 1), 0.5 * (n.z + 1) }};
		return temp3;
	}

	vec3 unit_direction = vec3_norm(&r->direction);
	hit = 0.5 * (unit_direction.y + 1.0);

	color3 temp0 = {{ 1.0, 1.0, 1.0 }};
	color3 temp1 = {{ 0.5, 0.7, 1.0 }};
	color3 prod0 = vec3_multiply_double(&temp0, 1.0 - hit);
	color3 prod1 = vec3_multiply_double(&temp1, hit);
	/* blendedValue = (1 - t) * startValue + t * endValue */
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
			color3 pixel_color = ray_color(&r);

			write_color(stdout, &pixel_color);
		}
	}

	fprintf(stderr, "\nDone.\n");
}
