#include "camera.h"

#include "raykat.h"

#define FOCAL_LENGTH 1.0

camera camera_init(const point3* lookfrom,
		const point3* lookat,
		const vec3* vup,
		const f64 vfov,
		const f64 aspect_ratio,
		const f64 aperture,
		const f64 focus_dist) {
	const f64 theta = DEG_TO_RAD(vfov);
	const f64 h = tan(theta / 2);
	const f64 viewport_height = 2.0 * h;
	const f64 viewport_width = aspect_ratio * viewport_height;

	const vec3 temp0 = vec3_sub(lookfrom, lookat);
	const vec3 w = vec3_norm(&temp0);
	const vec3 temp1 = vec3_crossprod(vup, &w);
	const vec3 u = vec3_norm(&temp1);
	const vec3 v = vec3_crossprod(&w, &u);

	const point3 origin = *lookfrom;
	const vec3 horizontal = vec3_multiply_double(&u, viewport_width * focus_dist);
	const vec3 vertical = vec3_multiply_double(&v, viewport_height * focus_dist);

	const point3 half_hor = vec3_divide(&horizontal, 2);
	const point3 half_vert = vec3_divide(&vertical, 2);
	const point3 temp2 = vec3_sub(&origin, &half_hor);
	const point3 temp3 = vec3_sub(&temp2, &half_vert);
	const point3 temp4 = vec3_multiply_double(&w, focus_dist);
	const point3 lower_left_corner = vec3_sub(&temp3, &temp4);

	const f64 lens_radius = aperture / 2;

	const camera camera = {
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

ray camera_get_ray(const camera* cam, const f64 s, const f64 t) {
	const vec3 temp0 = vec3_random_in_unit_disk();
	const vec3 rd = vec3_multiply_double(&temp0, cam->lens_radius);

	const vec3 temp1 = vec3_multiply_double(&cam->u, rd.x);
	const vec3 temp2 = vec3_multiply_double(&cam->v, rd.y);
	const vec3 offset = vec3_add(&temp1, &temp2);

	const point3 h_pos = vec3_multiply_double(&cam->horizontal, s);
	const point3 v_pos = vec3_multiply_double(&cam->vertical, t);
	const point3 temp3 = vec3_add(&cam->lower_left_corner, &h_pos);
	const point3 temp4 = vec3_add(&temp3, &v_pos);
	const point3 direction = vec3_sub(&temp4, &cam->origin);

	const ray ray = { vec3_add(&cam->origin, &offset), vec3_sub(&direction, &offset) };

	return ray;
}
