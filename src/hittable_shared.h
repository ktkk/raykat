#ifndef HITTABLE_SHARED_H
#define HITTABLE_SHARED_H

#include <stdbool.h>

#include "hittable.h"

typedef enum {
	HITTABLE_TYPE_UNKNOWN = -1,
	HITTABLE_TYPE_SPHERE = 0,
	HITTABLE_TYPE_TRIANGLE,
} hittable_type;

typedef bool (*hittable_hit_fn)(const hittable* hittable,
		const ray* r,
		const f64 t_min,
		const f64 t_max,
		hit_record* rec);
typedef void (*hittable_delete_fn)(const hittable* hittable);

struct hittable_s {
	hittable_type type;

	hittable_hit_fn hit;
	hittable_delete_fn delete;
};

void hittable_init(hittable* hittable, const hittable_type type, hittable_hit_fn hit_fn, hittable_delete_fn delete_fn);

#endif //HITTABLE_SHARED_H
