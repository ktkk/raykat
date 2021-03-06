#ifndef HITTABLE_H
#define HITTABLE_H

#include "material.h"

#include "ray.h"
#include "hit_record.h"

typedef struct hittable_s hittable;

void hittable_delete(const hittable* hittable);
bool hittable_hit(const hittable* hittable, const ray* r, const f64 t_min, const f64 t_max, hit_record* rec);

#endif //HITTABLE_H
