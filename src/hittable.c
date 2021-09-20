#include "hittable.h"

void hittable_set_face_normal(hit_record* rec, ray* r, vec3* outward_normal) {
	rec->front_face = vec3_dotprod(&r->direction, outward_normal);
	vec3 inverse_outward_normal = vec3_invert(outward_normal);
	rec->normal = rec->front_face ? *outward_normal : inverse_outward_normal;
}
