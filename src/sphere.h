#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>

#include "hittable.h"
#include "vec3.h"
#include "ray.h"

typedef struct {
	point3 center;
	double radius;
} sphere;

bool sphere_hit(sphere* s, ray* r, double t_min, double t_max, hit_record* rec);

#endif //SPHERE_H
