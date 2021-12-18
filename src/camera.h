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

camera camera_init(point3* lookfrom,
		   point3* lookat,
		   vec3* vup,
		   double vfov,
		   double aspect_ratio,
		   double aperture,
		   double focus_dist);
ray camera_get_ray(camera* cam, double u, double v);

#endif //CAMERA_H
