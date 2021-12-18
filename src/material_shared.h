#ifndef MATERIAL_SHARED_H
#define MATERIAL_SHARED_H

#include "material.h"

typedef enum {
	MATERIAL_TYPE_UNKNOWN = -1,
	MATERIAL_TYPE_LAMBERTIAN = 0,
	MATERIAL_TYPE_METAL,
	MATERIAL_TYPE_DIELECTRIC,
} material_type;

typedef bool (*material_scatter_fn)(material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered);
typedef void (*material_delete_fn)(material* material);

struct material_s {
	material_type type;

	material_scatter_fn scatter;
	material_delete_fn delete;
};

void material_init(material* material, material_type type, material_scatter_fn scatter_fn, material_delete_fn delete_fn);

#endif //MATERIAL_SHARED_H
