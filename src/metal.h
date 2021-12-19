#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "material_shared.h"

typedef struct {
	material base;

	color3 albedo;
	double fuzz;
} metal;

material* metal_new(const color3* albedo, const double fuzz);
void metal_delete(const material* material);

#endif //METAL_H
