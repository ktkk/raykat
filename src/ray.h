#ifndef RAY_H
#define RAY_H

#include "raykat.h"

#include "vec3.h"

typedef struct {
	point3 origin;
	vec3 direction;
} ray;

point3 ray_at(const ray* r, const f64 t);

#endif //RAY_H
