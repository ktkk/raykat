#include <stdlib.h>
#include <stdio.h>

#include "vec3.h"
#include "lambertian.h"
#include "hittable.h"

static bool lambertian_scatter(const material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered);

material* lambertian_new(const color3* albedo) {
	lambertian* plambertian = (lambertian*)calloc(1, sizeof(*plambertian));
	if (plambertian == NULL) fprintf(stderr, "Calloc failed: %p\n", plambertian);

	material_init(&plambertian->base, MATERIAL_TYPE_LAMBERTIAN, lambertian_scatter, lambertian_delete);
	plambertian->albedo = *albedo;

	return (material*)plambertian;
}

static bool lambertian_scatter(const material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered) {
	if (material == NULL) fprintf(stderr, "Material is NULL: %p\n", material);
	if (material->type != MATERIAL_TYPE_LAMBERTIAN) fprintf(stderr, "Material is not lambertian but %d\n", material->type);

	(void)r_in;

	const lambertian* plambertian = (lambertian*)material;

	const vec3 temp0 = vec3_random_unit_vector();
	vec3 scatter_direction = vec3_add(&rec->normal, &temp0);

	if (vec3_near_zero(&scatter_direction))
		scatter_direction = rec->normal;

	const ray temp1 = { rec->p, scatter_direction };
	*scattered = temp1;
	*attenuation = plambertian->albedo;

	return true;
}

void lambertian_delete(const material* material) {
	if (material == NULL) fprintf(stderr, "Material is NULL: %p\n", material);
	if (material->type != MATERIAL_TYPE_LAMBERTIAN) fprintf(stderr, "Material is not lambertian but %d\n", material->type);

	lambertian* plambertian = (lambertian*)material;
	free(plambertian);
}
