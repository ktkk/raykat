#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>

#include "hittable.h"
#include "hittable_shared.h"
#include "vec3.h"
#include "ray.h"

typedef struct {
	hittable base;

	point3 center;
	double radius;
	material* mat_ptr;
} sphere;

sphere sphere_init(const point3* center, const double radius, material* material);
hittable* sphere_new(const point3* center, const double radius, material* material);
bool sphere_hit(const hittable* hittable, const ray* r, const double t_min, const double t_max, hit_record* rec);
void sphere_delete(const hittable* hittable);

#endif //SPHERE_H
