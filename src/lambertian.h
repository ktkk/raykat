#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "material_shared.h"

typedef struct {
	material base;

	color3 albedo;
} lambertian;

material* lambertian_new(const color3* albedo);
void lambertian_delete(const material* material);

#endif //LAMBERTIAN_H
