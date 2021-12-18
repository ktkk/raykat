#include "camera.h"

#include "raykat.h"

#define FOCAL_LENGTH 1.0

camera camera_init(point3* lookfrom, point3* lookat, vec3* vup, double vfov, double aspect_ratio, double aperture, double focus_dist) {
	double theta = DEG_TO_RAD(vfov);
	double h = tan(theta / 2);
	double viewport_height = 2.0 * h;
	double viewport_width = aspect_ratio * viewport_height;

	vec3 temp0 = vec3_sub(lookfrom, lookat);
	vec3 w = vec3_norm(&temp0);
	vec3 temp1 = vec3_crossprod(vup, &w);
	vec3 u = vec3_norm(&temp1);
	vec3 v = vec3_crossprod(&w, &u);

	point3 origin = *lookfrom;
	vec3 horizontal = vec3_multiply_double(&u, viewport_width * focus_dist);
	vec3 vertical = vec3_multiply_double(&v, viewport_height * focus_dist);

	point3 half_hor = vec3_divide(&horizontal, 2);
	point3 half_vert = vec3_divide(&vertical, 2);
	point3 temp2 = vec3_sub(&origin, &half_hor);
	point3 temp3 = vec3_sub(&temp2, &half_vert);
	point3 temp4 = vec3_multiply_double(&w, focus_dist);
	point3 lower_left_corner = vec3_sub(&temp3, &temp4);

	double lens_radius = aperture / 2;

	camera camera = {
		.origin = origin,
		.lower_left_corner = lower_left_corner,
		.horizontal = horizontal,
		.vertical = vertical,
		.u = u,
		.v = v,
		.w = w,
		.lens_radius = lens_radius,
	};

	return camera;
}

ray camera_get_ray(camera* cam, double s, double t) {
	vec3 temp0 = vec3_random_in_unit_disk();
	vec3 rd = vec3_multiply_double(&temp0, cam->lens_radius);

	vec3 temp1 = vec3_multiply_double(&cam->u, rd.x);
	vec3 temp2 = vec3_multiply_double(&cam->v, rd.y);
	vec3 offset = vec3_add(&temp1, &temp2);

	point3 h_pos = vec3_multiply_double(&cam->horizontal, s);
	point3 v_pos = vec3_multiply_double(&cam->vertical, t);
	point3 temp3 = vec3_add(&cam->lower_left_corner, &h_pos);
	point3 temp4 = vec3_add(&temp3, &v_pos);
	point3 direction = vec3_sub(&temp4, &cam->origin);

	ray ray = { vec3_add(&cam->origin, &offset), vec3_sub(&direction, &offset) };

	return ray;
}
