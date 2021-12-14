#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "material_shared.h"

typedef struct {
	material base;

	color3 albedo;
} metal;

material* metal_new(color3* albedo);
void metal_delete(material* material);

#endif //METAL_H
