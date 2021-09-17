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

/* vec3 operations */
vec3 vec3_invert(vec3* v);

vec3 vec3_add(vec3* v0, vec3* v1);
vec3 vec3_sub(vec3* v0, vec3* v1);
vec3 vec3_multiply_vectors(vec3* v0, vec3* v1);
vec3 vec3_multiply_double(vec3* v, double t);
vec3 vec3_divide(vec3* v, double t);

double vec3_dotprod(vec3* v0, vec3* v1);
vec3 vec3_crossprod(vec3* v0, vec3* v1);
double vec3_length_squared(vec3* v);
double vec3_length(vec3* v);
vec3 vec3_norm(vec3* v);

/* Typedef point and color as alias to vec3 */
typedef vec3 point3;
typedef vec3 color3;

#endif //VEC3_H
