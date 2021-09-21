#include <stdlib.h>
#include <stdio.h>
#include "hittable_list.h"

hittable_list hittable_list_init(int capacity) {
	hittable_list* list = calloc(1, sizeof(hittable_list));
	if (list == NULL) fprintf(stderr, "Calloc failed: %p", list);

	list->objects.capacity = capacity;
	list->objects.size = 0;
	list->objects.data = calloc(list->objects.capacity, sizeof(hittable*));
	if (list->objects.data == NULL) fprintf(stderr, "Calloc failed: %p", list->objects.data);

	return *list;
}

void hittable_list_clear(hittable_list* list) {
	int capacity = list->objects.capacity;

	*list = hittable_list_init(capacity);
}

void hittable_list_add(hittable_list* list, hittable* object) {
	if (list == NULL) fprintf(stderr, "List is NULL: %p", list);

	/* Check capacity */
	if (list->objects.size > list->objects.capacity) {
		list->objects.data = realloc(list->objects.data, list->objects.capacity * 2 * sizeof(hittable*));
		if (list->objects.data == NULL) fprintf(stderr, "Realloc failed: %p", list->objects.data);

		list->objects.capacity *= 2;
	}

	list->objects.data[list->objects.size++] = object;
}

bool hittable_list_hit(hittable_list* list, ray* r, double t_min, double t_max, hit_record* rec) {
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;

	for (int i = 0; i < list->objects.size; ++i) {
		if (hittable_hit(list->objects.data[i], r, t_min, closest_so_far, &temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
	}

	return hit_anything;
}
