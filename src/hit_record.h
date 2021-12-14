#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <stdbool.h>

#include "vec3.h"
#include "ray.h"

typedef struct {
	point3 p;
	vec3 normal;
	void* mat_ptr;
	double t;

	bool front_face;
} hit_record;

void hit_record_set_face_normal(hit_record* rec, ray* r, vec3* outward_normal);

#endif //HIT_RECORD_H
