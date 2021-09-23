#include "camera.h"

#define ASPECT_RATIO (16.0/9.0)

#define VIEW_HEIGHT 2.0
#define VIEW_WIDTH ASPECT_RATIO * VIEW_HEIGHT
#define FOCAL_LENGTH 1.0

camera camera_init() {
	point3 origin = {{ 0, 0, 0 }};
	vec3 horizontal = {{ VIEW_WIDTH, 0, 0 }};
	vec3 vertical = {{ 0, VIEW_HEIGHT, 0 }};

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
