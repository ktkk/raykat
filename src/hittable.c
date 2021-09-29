#include "hittable.h"
#include "hittable_shared.h"

void hittable_init(hittable* hittable, hittable_type type, hittable_hit_fn hit_fn) {
	hittable->type = type;
	hittable->hit = hit_fn;
}

bool hittable_hit(hittable* hittable, ray* r, double t_min, double t_max, hit_record* rec) {
	return hittable->hit(hittable, r, t_min, t_max, rec);
}

void hit_record_set_face_normal(hit_record* rec, ray* r, vec3* outward_normal) {
	rec->front_face = vec3_dotprod(&r->direction, outward_normal) < 0;
	vec3 inverse_outward_normal = vec3_invert(outward_normal);
	rec->normal = rec->front_face ? *outward_normal : inverse_outward_normal;
}
