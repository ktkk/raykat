#include <stddef.h>

#include "material.h"
#include "material_shared.h"

void material_init(material* material, const material_type type, material_scatter_fn scatter_fn, material_delete_fn delete_fn) {
	material->type = type;

	material->scatter = scatter_fn;
	material->delete = delete_fn;
}

void material_delete(const material* material) {
	if (material == NULL) return;

	material->delete(material);
}

bool material_scatter(const material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered) {
	return material->scatter(material, r_in, rec, attenuation, scattered);
}
