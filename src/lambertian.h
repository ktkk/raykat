#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "material_shared.h"

typedef struct {
	material base;

	color3 albedo;
} lambertian;

lambertian lambertian_init(color3* aledo);
material* lambertian_new(color3* albedo);
bool lambertian_scatter(material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered);
void lambertian_delete(material* material);

#endif //LAMBERTIAN_H
