#ifndef SPHERE_H
#define SPHERE_H

#include "raykat.h"

#include "hittable.h"
#include "hittable_shared.h"

#include "vec3.h"
#include "ray.h"

typedef struct {
	hittable base;

	point3 center;
	f64 radius;
	material* mat_ptr;
} sphere;

sphere sphere_init(const point3* center, const f64 radius, material* material);
hittable* sphere_new(const point3* center, const f64 radius, material* material);
bool sphere_hit(const hittable* hittable,
		const ray* r,
		const f64 t_min,
		const f64 t_max,
		hit_record* rec);
void sphere_delete(const hittable* hittable);

#endif //SPHERE_H
