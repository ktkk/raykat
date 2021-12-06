#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>

#include "hittable.h"
#include "hittable_shared.h"
#include "material.h"
#include "material_shared.h"
#include "vec3.h"
#include "ray.h"

typedef struct {
	hittable base;

	point3 center;
	double radius;
	struct material* mat_ptr;
} sphere;

sphere sphere_init(point3* center, double radius, material* material);
hittable* sphere_new(point3* center, double radius, material* material);
bool sphere_hit(hittable* hittable, ray* r, double t_min, double t_max, hit_record* rec);
void sphere_delete(hittable* hittable);

#endif //SPHERE_H
