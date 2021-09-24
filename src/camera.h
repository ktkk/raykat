#ifndef CAMERA_H
#define CAMERA_H

#include "raykat.h"

typedef struct {
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
} camera;

camera camera_init(double vfov, double aspect_ratio);
ray camera_get_ray(camera* cam, double u, double v);

#endif //CAMERA_H
