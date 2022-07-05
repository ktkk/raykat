#include "ray.h"

point3 ray_at(const ray* r, const f64 t) {
	const vec3 tmp = vec3_multiply_double(&r->direction, t);
	return vec3_add(&r->origin, &tmp);
}
