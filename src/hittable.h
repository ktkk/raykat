#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"

typedef struct {
	point3 p;
	vec3 normal;
	double t;
} hit_record;

#endif //HITTABLE_H
