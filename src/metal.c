#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "metal.h"
#include "hittable.h"
#include "vec3.h"

static bool metal_scatter(material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered);

material* metal_new(color3* albedo, double fuzz) {
	metal* pmetal = (metal*)calloc(1, sizeof(*pmetal));
	if (pmetal == NULL) fprintf(stderr, "Calloc failed: %p\n", pmetal);

	material_init(&pmetal->base, MATERIAL_TYPE_METAL, metal_scatter, metal_delete);
	pmetal->albedo = *albedo;
	pmetal->fuzz = fuzz < 1 ? fuzz : 1;

	return (material*)pmetal;
}

bool metal_scatter(material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered) {
	if (material == NULL) fprintf(stderr, "Material is NULL: %p\n", material);
	if (material->type != MATERIAL_TYPE_METAL) fprintf(stderr, "Material is not metal but %d\n", material->type);

	metal* pmetal = (metal*)material;

	vec3 temp0 = vec3_norm(&r_in->direction);
	vec3 reflected = vec3_reflect(&temp0, &rec->normal);

	vec3 temp1 = vec3_random_in_unit_sphere();
	vec3 temp2 = vec3_multiply_double(&temp1, pmetal->fuzz);
	ray temp3 = { rec->p, vec3_add(&reflected, &temp2) };
	*scattered = temp3;
	*attenuation = pmetal->albedo;

	return vec3_dotprod(&scattered->direction, &rec->normal) > 0;
}

void metal_delete(material* material) {
	if (material == NULL) fprintf(stderr, "Material is NULL: %p\n", material);
	if (material->type != MATERIAL_TYPE_METAL) fprintf(stderr, "Material is not metal but %d\n", material->type);

	metal* pmetal = (metal*)material;
	free(pmetal);
}
