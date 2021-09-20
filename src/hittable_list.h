#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

typedef struct {
	struct {
		int size;
		int capacity;
		hittable** data;
	} objects;
} hittable_list;

void hittable_list_clear();
void hittable_list_add(hittable_list* list, hittable* objects);
bool hittable_list_hit(hittable_list* list, ray* r, double t_min, double t_max, hit_record* rec);

#endif //HITTABLE_LIST_H
