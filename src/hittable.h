#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>

#include "ray.h"

typedef struct {
	point3 p;
	vec3 normal;
	double t;

	bool front_face;
} hit_record;

typedef struct hittable_s hittable;

bool hittable_hit(hittable* hittable, ray* r, double t_min, double t_max, hit_record* rec);

void hit_record_set_face_normal(hit_record* rec, ray* r, vec3* outward_normal);

#endif //HITTABLE_H
