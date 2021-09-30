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

triangle triangle_init(point3* p0, point3* p1, point3* p2);
hittable* triangle_new(point3* p0, point3* p1, point3* p2);
bool triangle_hit(hittable* hittable, ray* r, double t_min, double t_max, hit_record* rec);
void triangle_delete(hittable* hittable);

#endif //TRIANGLE_H
