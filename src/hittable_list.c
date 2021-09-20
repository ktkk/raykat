#include "hittable_list.h"

void hittable_list_clear() {
	// TODO(): Figure out how to clear pseudo vector
}

void hittable_list_add(hittable_list* list, hittable* objects) {
	// TODO(): Figure out how to add to pseudo vector
}

bool hittable_list_hit(hittable_list* list, ray* r, double t_min, double t_max, hit_record* rec) {
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;

	for (int i = 0; i < list->objects.size; ++i) {
		// TODO(): Figure out psuedo virtual functions of hittable
	}

	return hit_anything;
}
