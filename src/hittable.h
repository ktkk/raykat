#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "hit_record.h"
#include "material.h"

typedef struct hittable_s hittable;

void hittable_delete(const hittable* hittable);
bool hittable_hit(const hittable* hittable, const ray* r, const double t_min, const double t_max, hit_record* rec);

#endif //HITTABLE_H
