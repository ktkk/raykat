#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

typedef struct {
	struct {
		int size, capacity;
		hittable** data;
	} objects;
} hittable_list;

hittable_list hittable_list_init(int capacity);
void hittable_list_cleanup(hittable_list* list);
void hittable_list_add(hittable_list* list, hittable* objects);
bool hittable_list_hit(hittable_list* list, ray* r, double t_min, double t_max, hit_record* rec);

#endif //HITTABLE_LIST_H
