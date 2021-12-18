#ifndef VEC3_H
#define VEC3_H

#define VEC3_SIZE 3

typedef	union {
	double v[VEC3_SIZE];

	struct {
		double x;
		double y;
		double z;
	};
	struct {
		double r;
		double g;
		double b;
	};
} vec3;

#ifndef VEC3DEF
#define VEC3DEF static inline
#endif //VEC3DEF

/* Typedef point and color as alias to vec3 */
typedef vec3 point3;
typedef vec3 color3;

#include <math.h>
#include <stdbool.h>
#include "raykat.h"

/* vec3 operations */
VEC3DEF vec3 vec3_invert(const vec3* v) {
	vec3 inverse = {{ -v->v[0], -v->v[1], -v->v[2] }};
	return inverse;
}

VEC3DEF vec3 vec3_add(const vec3* v0, const vec3* v1) {
	vec3 sum = {{ v0->v[0] + v1->v[0], v0->v[1] + v1->v[1], v0->v[2] + v1->v[2] }};
	return sum;
}

VEC3DEF vec3 vec3_sub(const vec3* v0, const vec3* v1) {
	vec3 sub = {{ v0->v[0] - v1->v[0], v0->v[1] - v1->v[1], v0->v[2] - v1->v[2] }};
	return sub;
}

VEC3DEF vec3 vec3_multiply_vectors(const vec3* v0, const vec3* v1) {
	vec3 prod = {{ v0->v[0] * v1->v[0], v0->v[1] * v1->v[1], v0->v[2] * v1->v[2] }};
	return prod;
}

VEC3DEF vec3 vec3_multiply_double(const vec3* v, double t) {
	vec3 prod = {{ t * v->v[0], t * v->v[1], t * v->v[2] }};
	return prod;
}

VEC3DEF vec3 vec3_divide(const vec3* v, double t) {
	return vec3_multiply_double(v, (1/t));
}

VEC3DEF double vec3_dotprod(const vec3* v0, const vec3* v1) {
	return v0->v[0] * v1->v[0]
	     + v0->v[1] * v1->v[1]
	     + v0->v[2] * v1->v[2];
}

VEC3DEF vec3 vec3_crossprod(const vec3* v0, const vec3* v1) {
	vec3 cross = {{
		v0->v[1] * v1->v[2] - v0->v[2] * v1->v[1],
		v0->v[2] * v1->v[0] - v0->v[0] * v1->v[2],
		v0->v[0] * v1->v[1] - v0->v[1] * v1->v[0]
	}};
	return cross;
}

VEC3DEF double vec3_length_squared(const vec3* v) {
	/* Pythagoras' theorem */
	return v->v[0] * v->v[0] + v->v[1] * v->v[1] + v->v[2] * v->v[2];
}

VEC3DEF double vec3_length(const vec3* v) {
	return sqrt(vec3_length_squared(v));
}

VEC3DEF vec3 vec3_norm(const vec3* v) {
	return vec3_divide(v, vec3_length(v));
}

VEC3DEF vec3 vec3_reflect(const vec3* v, const vec3* n) {
	vec3 temp = vec3_multiply_double(n, vec3_dotprod(v, n) * 2);
	return vec3_sub(v, &temp);
}

VEC3DEF vec3 vec3_refract(const vec3* uv, const vec3* n, double etai_over_etat) {
	vec3 temp0 = vec3_invert(uv);
	double temp1 = vec3_dotprod(&temp0, n);
	double cos_theta = fmin(temp1, 1.0);

	vec3 temp2 = vec3_multiply_double(n, cos_theta);
	vec3 temp3 = vec3_add(uv, &temp2);
	vec3 r_out_perp = vec3_multiply_double(&temp3, etai_over_etat);
	vec3 r_out_parallel = vec3_multiply_double(n, -sqrt(fabs(1.0 - vec3_length_squared(&r_out_perp))));

	return vec3_add(&r_out_perp, &r_out_parallel);
}

/* vec3 random generators */
VEC3DEF vec3 vec3_random() {
	vec3 temp = {{ RAND_DOUBLE, RAND_DOUBLE, RAND_DOUBLE }};
	return temp;
}

VEC3DEF vec3 vec3_random_range(double min, double max) {
	vec3 temp = {{ RAND_DOUBLE_RANGE(min, max), RAND_DOUBLE_RANGE(min, max), RAND_DOUBLE_RANGE(min, max) }};
	return temp;
}

VEC3DEF vec3 vec3_random_in_unit_sphere() {
	while (1) {
		vec3 p = vec3_random_range(-1, 1);

		if (vec3_length_squared(&p) >= 1) continue;

		return p;
	}
}

VEC3DEF vec3 vec3_random_unit_vector() {
	vec3 rand = vec3_random_in_unit_sphere();
	return vec3_norm(&rand);
}

VEC3DEF vec3 vec3_random_in_hemisphere(const vec3* normal) {
	vec3 in_unit_sphere = vec3_random_in_unit_sphere();
	if (vec3_dotprod(&in_unit_sphere, normal) > 0.0)
		return in_unit_sphere;
	else
		return vec3_invert(&in_unit_sphere);
}

VEC3DEF vec3 vec3_random_in_unit_disk() {
	while (1) {
		vec3 p = {{ RAND_DOUBLE_RANGE(-1, 1), RAND_DOUBLE_RANGE(-1, 1), 0 }};

		if (vec3_length_squared(&p) >= 1) continue;

		return p;
	}
}

VEC3DEF bool vec3_near_zero(vec3* v) {
	const double s = 1e-8;
	return (fabs(v->v[0]) < s) && (fabs(v->v[1]) < s) && (fabs(v->v[2]) < s);
}

#endif //VEC3_H
