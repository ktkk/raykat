#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "material_shared.h"

typedef struct {
	material base;

	color3 albedo;
} metal;

metal metal_init(color3* aledo);
material* metal_new(color3* albedo);
bool metal_scatter(material* material, const ray* r_in, const struct hit_record* rec, color3* attenuation, ray* scattered);
void metal_delete(material* material);

#endif //METAL_H
