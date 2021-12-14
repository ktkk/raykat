#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "hit_record.h"
#include "material.h"

typedef struct hittable_s hittable;

void hittable_delete(hittable* hittable);
bool hittable_hit(hittable* hittable, ray* r, double t_min, double t_max, hit_record* rec);

#endif //HITTABLE_H
