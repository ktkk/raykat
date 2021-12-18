#ifndef VEC3_H
#define VEC3_H

#include <stdbool.h>

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

/* vec3 operations */
vec3 vec3_invert(const vec3* v);

vec3 vec3_add(const vec3* v0, const vec3* v1);
vec3 vec3_sub(const vec3* v0, const vec3* v1);
vec3 vec3_multiply_vectors(const vec3* v0, const vec3* v1);
vec3 vec3_multiply_double(const vec3* v, double t);
vec3 vec3_divide(const vec3* v, double t);

double vec3_dotprod(const vec3* v0, const vec3* v1);
vec3 vec3_crossprod(const vec3* v0, const vec3* v1);
double vec3_length_squared(const vec3* v);
double vec3_length(const vec3* v);
vec3 vec3_norm(const vec3* v);
vec3 vec3_reflect(const vec3* v, const vec3* n);
vec3 vec3_refract(const vec3* uv, const vec3* n, double etai_over_etat);

/* vec3 random generators */
vec3 vec3_random();
vec3 vec3_random_range(double min, double max);
vec3 vec3_random_in_unit_sphere();
vec3 vec3_random_unit_vector();
vec3 vec3_random_in_hemisphere(const vec3* normal);
vec3 vec3_random_in_unit_disk();

bool vec3_near_zero(vec3* v);

/* Typedef point and color as alias to vec3 */
typedef vec3 point3;
typedef vec3 color3;

#endif //VEC3_H
