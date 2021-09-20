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

typedef struct {
	// TODO(): Figure out virtual function "hit", possibly with function pointers
} hittable;

void hittable_set_face_normal(hit_record* rec, ray* r, vec3* outward_normal);

#endif //HITTABLE_H
