#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

typedef struct {
	usize size, capacity;
	hittable** data;
} hittable_list;

hittable_list* hittable_list_init(const usize capacity);
void hittable_list_cleanup(hittable_list* list);
void hittable_list_add(hittable_list* list, hittable* objects);
bool hittable_list_hit(const hittable_list* list, const ray* r, const f64 t_min, const f64 t_max, hit_record* rec);

#endif //HITTABLE_LIST_H
