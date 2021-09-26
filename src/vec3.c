#include <math.h>
#include "raykat.h"
#include "vec3.h"

vec3 vec3_invert(const vec3* v) {
	vec3 inverse = {{ -v->v[0], -v->v[1], -v->v[2] }};
	return inverse;
}

vec3 vec3_add(const vec3* v0, const vec3* v1) {
	vec3 sum = {{ v0->v[0] + v1->v[0], v0->v[1] + v1->v[1], v0->v[2] + v1->v[2] }};
	return sum;
}

vec3 vec3_sub(const vec3* v0, const vec3* v1) {
	vec3 sub = {{ v0->v[0] - v1->v[0], v0->v[1] - v1->v[1], v0->v[2] - v1->v[2] }};
	return sub;
}

vec3 vec3_multiply_vectors(const vec3* v0, const vec3* v1) {
	vec3 prod = {{ v0->v[0] * v1->v[0], v0->v[1] * v1->v[1], v0->v[2] * v1->v[2] }};
	return prod;
}

vec3 vec3_multiply_double(const vec3* v, double t) {
	vec3 prod = {{ t * v->v[0], t * v->v[1], t * v->v[2] }};
	return prod;
}

vec3 vec3_divide(const vec3* v, double t) {
	return vec3_multiply_double(v, (1/t));
}

double vec3_dotprod(const vec3* v0, const vec3* v1) {
	return v0->v[0] * v1->v[0]
	     + v0->v[1] * v1->v[1]
	     + v0->v[2] * v1->v[2];
}

vec3 vec3_crossprod(const vec3* v0, const vec3* v1) {
	vec3 cross = {{
		v0->v[1] * v1->v[2] - v0->v[2] * v1->v[1],
		v0->v[2] * v1->v[0] - v0->v[0] * v1->v[2],
		v0->v[0] * v1->v[1] - v0->v[1] * v1->v[0]
	}};
	return cross;
}

double vec3_length_squared(const vec3* v) {
	/* Pythagoras' theorem */
	return v->v[0] * v->v[0] + v->v[1] * v->v[1] + v->v[2] * v->v[2];
}

double vec3_length(const vec3* v) {
	return sqrt(vec3_length_squared(v));
}

vec3 vec3_norm(const vec3* v) {
	return vec3_divide(v, vec3_length(v));
}

vec3 vec3_random() {
	vec3 temp = {{ RAND_DOUBLE, RAND_DOUBLE, RAND_DOUBLE }};
	return temp;
}

vec3 vec3_random_range(double min, double max) {
	vec3 temp = {{ RAND_DOUBLE_RANGE(min, max), RAND_DOUBLE_RANGE(min, max), RAND_DOUBLE_RANGE(min, max) }};
	return temp;
}

vec3 vec3_random_in_unit_sphere() {
	while (1) {
		vec3 p = vec3_random_range(-1, 1);

		if (vec3_length_squared(&p) >= 1) continue;

		return p;
	}
}

vec3 vec3_random_unit_vector() {
	vec3 rand = vec3_random_in_unit_sphere();
	return vec3_norm(&rand);
}

vec3 vec3_random_in_hemisphere(const vec3* normal) {
	vec3 in_unit_sphere = vec3_random_in_unit_sphere();
	if (vec3_dotprod(&in_unit_sphere, normal) > 0.0)
		return in_unit_sphere;
	else
		return vec3_invert(&in_unit_sphere);
}

vec3 vec3_random_in_unit_disk() {
	while (1) {
		vec3 p = {{ RAND_DOUBLE_RANGE(-1, 1), RAND_DOUBLE_RANGE(-1, 1), 0 }};

		if (vec3_length_squared(&p) >= 1) continue;

		return p;
	}
}
