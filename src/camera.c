#include "raykat.h"

#include "camera.h"

#define FOCAL_LENGTH 1.0

camera camera_init(double vfov, double aspect_ratio) {
	double theta = DEG_TO_RAD(vfov);
	double h = tan(theta / 2);
	double viewport_height = 2.0 * h;
	double viewport_width = aspect_ratio * viewport_height;

	point3 origin = {{ 0, 0, 0 }};
	vec3 horizontal = {{ viewport_width, 0, 0 }};
	vec3 vertical = {{ 0, viewport_height, 0 }};

	point3 half_hor = vec3_divide(&horizontal, 2);
	point3 half_vert = vec3_divide(&vertical, 2);
	point3 temp0 = vec3_sub(&origin, &half_hor);
	point3 temp1 = vec3_sub(&temp0, &half_vert);
	point3 temp2 = {{ 0, 0, FOCAL_LENGTH }};
	point3 lower_left_corner = vec3_sub(&temp1, &temp2);

	camera camera = {
		.origin = origin,
		.lower_left_corner = lower_left_corner,
		.horizontal = horizontal,
		.vertical = vertical,
	};

	return camera;
}

ray camera_get_ray(camera* cam, double u, double v) {
	point3 h_pos = vec3_multiply_double(&cam->horizontal, u);
	point3 v_pos = vec3_multiply_double(&cam->vertical, v);
	point3 temp0 = vec3_add(&cam->lower_left_corner, &h_pos);
	point3 temp1 = vec3_add(&temp0, &v_pos);
	point3 direction = vec3_sub(&temp1, &cam->origin);

	ray ray = { cam->origin, direction };

	return ray;
}
