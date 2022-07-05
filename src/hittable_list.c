#include <stdlib.h>
#include <stdio.h>

#include "hittable_list.h"

hittable_list* hittable_list_init(const usize capacity) {
	hittable_list* list = (hittable_list*)calloc(1, sizeof(*list));
	if (list == NULL) fprintf(stderr, "Calloc failed: %p\n", list);

	list->data = (hittable**)calloc(capacity, sizeof(*list->data));
	if (list->data == NULL) fprintf(stderr, "Calloc failed: %p\n", list->data);

	list->capacity = capacity;
	list->size = 0;

	return list;
}

void hittable_list_cleanup(hittable_list* list) {
	if (list == NULL) fprintf(stderr, "List is NULL: %p\n", list);

	for (usize i = 0; i < list->size; ++i) {
		hittable_delete(list->data[i]);
	}

	free(list->data);

	list->size = 0;
	list->capacity = 0;
	list->data = NULL;

	free(list);
}

void hittable_list_add(hittable_list* list, hittable* object) {
	if (list == NULL) fprintf(stderr, "List is NULL: %p\n", list);

	/* Check capacity. Realloc before size is equal to capacity */
	if (list->size >= list->capacity) {
		list->data = (hittable**)realloc(list->data, list->capacity * 2 * sizeof(hittable*));
		if (list->data == NULL) fprintf(stderr, "Realloc failed: %p\n", list->data);

		list->capacity *= 2;
	}

	list->data[list->size++] = object;
}

bool hittable_list_hit(const hittable_list* list, const ray* r, const f64 t_min, const f64 t_max, hit_record* rec) {
	if (list == NULL) fprintf(stderr, "List is NULL: %p\n", list);

	hit_record temp_rec;
	bool hit_anything = false;
	f64 closest_so_far = t_max;

	for (usize i = 0; i < list->size; ++i) {
		if (hittable_hit(list->data[i], r, t_min, closest_so_far, &temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
	}

	return hit_anything;
}
