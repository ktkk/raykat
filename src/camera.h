#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

typedef struct {
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
} camera;

camera camera_init(const point3* lookfrom,
		   const point3* lookat,
		   const vec3* vup,
		   const double vfov,
		   const double aspect_ratio,
		   const double aperture,
		   const double focus_dist);
ray camera_get_ray(const camera* cam, const double u, const double v);

#endif //CAMERA_H
