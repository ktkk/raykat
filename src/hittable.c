#include <stddef.h>
#include "hittable.h"
#include "hittable_shared.h"

void hittable_init(hittable* hittable, hittable_type type, hittable_hit_fn hit_fn, hittable_delete_fn delete_fn) {
	hittable->type = type;

	hittable->hit = hit_fn;
	hittable->delete = delete_fn;
}

void hittable_delete(hittable* hittable) {
	if (hittable == NULL) return;

	hittable->delete(hittable);
}

bool hittable_hit(hittable* hittable, ray* r, double t_min, double t_max, hit_record* rec) {
	return hittable->hit(hittable, r, t_min, t_max, rec);
}
