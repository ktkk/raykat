#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdbool.h>

#include "hittable.h"
#include "hittable_shared.h"
#include "vec3.h"
#include "ray.h"

typedef struct {
	hittable base;

	struct {
		point3 p0;
		point3 p1;
		point3 p2;
	};
} triangle;

triangle triangle_init(const point3* p0, const point3* p1, const point3* p2);
hittable* triangle_new(const point3* p0, const point3* p1, const point3* p2);
bool triangle_hit(const hittable* hittable, const ray* r, const double t_min, const double t_max, hit_record* rec);
void triangle_delete(const hittable* hittable);

#endif //TRIANGLE_H
