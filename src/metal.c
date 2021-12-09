#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "metal.h"
#include "hittable.h"
#include "vec3.h"

static bool metal_scatter_test(color3* albedo, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered);

metal metal_init(color3* albedo) {
	metal metal = { .albedo = *albedo };
	material_init(&metal.base, MATERIAL_TYPE_METAL, metal_scatter, metal_delete);

	return metal;
}

material* metal_new(color3* albedo) {
	metal* pmetal = (metal*)calloc(1, sizeof(*pmetal));
	if (pmetal = NULL) fprintf(stderr, "Calloc failed: %p\n", pmetal);

	*pmetal = metal_init(albedo);
	return (material*)pmetal;
}

bool metal_scatter(material* material, const ray* r_in, const struct hit_record* rec, color3* attenuation, ray* scattered) {
	if (material == NULL) fprintf(stderr, "Material is NULL: %p\n", material);
	if (material->type != MATERIAL_TYPE_METAL) fprintf(stderr, "Material is not metal but %d\n", material->type);

	metal* pmetal = (metal*)material;
	return metal_scatter_test(&pmetal->albedo, r_in, rec, attenuation, scattered);
}

void metal_delete(material* material) {
	if (material == NULL) fprintf(stderr, "Material is NULL: %p\n", material);
	if (material->type != MATERIAL_TYPE_METAL) fprintf(stderr, "Material is not metal but %d\n", material->type);

	metal* pmetal = (metal*)material;
	free(pmetal);
}

bool metal_scatter_test(color3* albedo, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered) {
	vec3 temp0 = vec3_norm(&r_in->direction);
	vec3 reflected = vec3_reflect(&temp0, &rec->normal);

	ray temp1 = { rec->p, reflected };
	*scattered = temp1;
	attenuation = albedo;

	return vec3_dotprod(&scattered->direction, &rec->normal) > 0;
}
