#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "sphere.h"

static bool sphere_hit_test(const point3* center,
		const f64 radius,
		material* mat_ptr,
		const ray* r,
		const f64 t_min,
		const f64 t_max,
		hit_record* rec);

sphere sphere_init(const point3* center, const f64 radius, material* material) {
	sphere sphere = { .center = *center, .radius = radius, .mat_ptr = material };
	hittable_init(&sphere.base, HITTABLE_TYPE_SPHERE, sphere_hit, sphere_delete);

	return sphere;
}

hittable* sphere_new(const point3* center, const f64 radius, material* material) {
	sphere* psphere = (sphere*)calloc(1, sizeof(*psphere));
	if (psphere == NULL) fprintf(stderr, "Calloc failed: %p\n", psphere);

	*psphere = sphere_init(center, radius, material);
	return (hittable*)psphere;
}

bool sphere_hit(const hittable* hittable,
		const ray* r,
		const f64 t_min,
		const f64 t_max,
		hit_record* rec) {
	if (hittable == NULL) fprintf(stderr, "Hittable is NULL: %p\n", hittable);
	if (hittable->type != HITTABLE_TYPE_SPHERE) fprintf(stderr, "Hittable is not sphere but %d\n", hittable->type);

	const sphere* psphere = (sphere*)hittable;
	return sphere_hit_test(&psphere->center, psphere->radius, psphere->mat_ptr, r, t_min, t_max, rec);
}

void sphere_delete(const hittable* hittable) {
	if (hittable == NULL) fprintf(stderr, "Hittable is NULL: %p\n", hittable);
	if (hittable->type != HITTABLE_TYPE_SPHERE) fprintf(stderr, "Hittable is not sphere but %d\n", hittable->type);

	sphere* psphere = (sphere*)hittable;

	material_delete(psphere->mat_ptr);

	free(psphere);
}

bool sphere_hit_test(const point3* center,
		const f64 radius,
		material* mat_ptr,
		const ray* r,
		const f64 t_min,
		const f64 t_max,
		hit_record* rec) {
	const vec3 oc = vec3_sub(&r->origin, center);
	const f64 a = vec3_length_squared(&r->direction);
	const f64 half_b = vec3_dotprod(&oc, &r->direction);
	const f64 c = vec3_length_squared(&oc) - radius * radius;
	const f64 discriminant = half_b * half_b - a * c;

	if (discriminant < 0) return false;
	const f64 sqrtd = sqrt(discriminant);

	/* Find the nearest root that lies in the acceptable range */
	f64 root = (-half_b - sqrtd) / a;
	if (root < t_min || root > t_max) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || root > t_max) return false;
	}

	rec->t = root;
	rec->p = ray_at(r, rec->t);
	const point3 temp0 = vec3_sub(&rec->p, center);
	const vec3 outward_normal = vec3_divide(&temp0, radius);
	hit_record_set_face_normal(rec, r, &outward_normal);
	rec->mat_ptr = mat_ptr;

	return true;
}
