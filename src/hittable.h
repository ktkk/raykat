#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>

#include "material.h"

#include "ray.h"

//struct material;

typedef struct {
	point3 p;
	vec3 normal;
	material* mat_ptr;
	double t;

	bool front_face;
} hit_record;

typedef struct hittable_s hittable;

void hittable_delete(hittable* hittable);
bool hittable_hit(hittable* hittable, ray* r, double t_min, double t_max, hit_record* rec);

void hit_record_set_face_normal(hit_record* rec, ray* r, vec3* outward_normal);

#endif //HITTABLE_H
