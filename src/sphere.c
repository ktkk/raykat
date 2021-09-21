#include <math.h>
#include "sphere.h"

bool sphere_hit(sphere* s, ray* r, double t_min, double t_max, hit_record* rec) {
	vec3 oc = vec3_sub(&r->origin, &s->center);
	double a = vec3_length_squared(&r->direction);
	double half_b = vec3_dotprod(&oc, &r->direction);
	double c = vec3_length_squared(&oc) - s->radius * s->radius;
	double discriminant = half_b * half_b - a * c;

	if (discriminant < 0) return false;
	double sqrtd = sqrt(discriminant);

	/* Find the nearest root that lies in the acceptable range */
	double root = (-half_b - sqrtd) / a;
	if (root < t_min || root > t_max) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || root > t_max) return false;
	}

	rec->t = root;
	rec->p = ray_at(r, rec->t);
	point3 temp0 = vec3_sub(&rec->p, &s->center);
	vec3 outward_normal = vec3_divide(&temp0, s->radius);
	hit_record_set_face_normal(rec, r, &outward_normal);

	return true;
}
