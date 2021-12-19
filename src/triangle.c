#include <stdlib.h>
#include <stdio.h>
#include "triangle.h"

#define EPSILON 0.000001

static bool triangle_hit_test(const point3* p0, const point3* p1, const point3* p2, const ray* r, const double t_min, const double t_max, hit_record* rec);

triangle triangle_init(const point3* p0, const point3* p1, const point3* p2) {
	triangle triangle = { .p0 = *p0, .p1 = *p1, .p2 = *p2 };
	hittable_init(&triangle.base, HITTABLE_TYPE_TRIANGLE, triangle_hit, triangle_delete);

	return triangle;
}

hittable* triangle_new(const point3* p0, const point3* p1, const point3* p2) {
	triangle* ptriangle = (triangle*)calloc(1, sizeof(*ptriangle));
	if (ptriangle == NULL) fprintf(stderr, "Calloc failed: %p\n", ptriangle);

	*ptriangle = triangle_init(p0, p1, p2);
	return (hittable*)ptriangle;
}

bool triangle_hit(const hittable* hittable, const ray* r, const double t_min, const double t_max, hit_record* rec) {
	if (hittable == NULL) fprintf(stderr, "Hittable is NULL: %p\n", hittable);
	if (hittable->type != HITTABLE_TYPE_TRIANGLE) fprintf(stderr, "Hittable is not triangle but %d\n", hittable->type);

	const triangle* ptriangle = (triangle*)hittable;
	return triangle_hit_test(&ptriangle->p0, &ptriangle->p1, &ptriangle->p2, r, t_min, t_max, rec);
}

void triangle_delete(const hittable* hittable) {
	if (hittable == NULL) fprintf(stderr, "Hittable is NULL: %p\n", hittable);
	if (hittable->type != HITTABLE_TYPE_TRIANGLE) fprintf(stderr, "Hittable is not triangle but %d\n", hittable->type);

	triangle* ptriangle = (triangle*)hittable;

	free(ptriangle);
}

bool triangle_hit_test(const point3* p0, const point3* p1, const point3* p2, const ray* r, const double t_min, const double t_max, hit_record* rec) {
	const vec3 edge0 = vec3_sub(p1, p0);
	const vec3 edge1 = vec3_sub(p2, p0);

	const vec3 pvec = vec3_crossprod(&r->direction, &edge1);
	const double determinant = vec3_dotprod(&edge0, &pvec);
	const double inv_determinant = 1.0 / determinant;
	if (determinant > -EPSILON && determinant < EPSILON) return false;

	const vec3 tvec = vec3_sub(&r->origin, p0);
	const double u = vec3_dotprod(&tvec, &pvec) * inv_determinant;
	if (u < 0.0 || u > 1.0) return false;

	const vec3 qvec = vec3_crossprod(&tvec, &edge0);
	const double v = vec3_dotprod(&r->direction, &qvec) * inv_determinant;
	if (v < 0.0 || u + v > 1.0) return false;

	const double t = vec3_dotprod(&edge1, &qvec) * inv_determinant;
	if (t < t_min || t > t_max) return false;

	rec->t = t;
	rec->p = ray_at(r, rec->t);
	const vec3 outward_normal = vec3_crossprod(&edge0, &edge1);
	hit_record_set_face_normal(rec, r, &outward_normal);

	return true;
}
