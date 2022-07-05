#ifndef CAMERA_H
#define CAMERA_H

#include "raykat.h"

#include "vec3.h"
#include "ray.h"

typedef struct {
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	f64 lens_radius;
} camera;

camera camera_init(const point3* lookfrom,
		   const point3* lookat,
		   const vec3* vup,
		   const f64 vfov,
		   const f64 aspect_ratio,
		   const f64 aperture,
		   const f64 focus_dist);
ray camera_get_ray(const camera* cam, const f64 u, const f64 v);

#endif //CAMERA_H
