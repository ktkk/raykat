#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lambertian.h"
#include "hittable.h"
#include "vec3.h"

static bool lambertian_scatter_test(color3* albedo, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered);

lambertian lambertian_init(color3* albedo) {
	lambertian lambertian = { .albedo = *albedo };
	material_init(&lambertian.base, MATERIAL_TYPE_LAMBERTIAN, lambertian_scatter, lambertian_delete);

	return lambertian;
}

material* lambertian_new(color3* albedo) {
	lambertian* plambertian = (lambertian*)calloc(1, sizeof(*plambertian));
	if (plambertian == NULL) fprintf(stderr, "Calloc failed: %p\n", plambertian);

	*plambertian = lambertian_init(albedo);
	return (material*)plambertian;
}

bool lambertian_scatter(material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered) {
	if (material == NULL) fprintf(stderr, "Material is NULL: %p\n", material);
	if (material->type != MATERIAL_TYPE_LAMBERTIAN) fprintf(stderr, "Material is not lambertian but %d\n", material->type);

	lambertian* plambertian = (lambertian*)material;
	return lambertian_scatter_test(&plambertian->albedo, r_in, rec, attenuation, scattered);
}

void lambertian_delete(material* material) {
	if (material == NULL) fprintf(stderr, "Material is NULL: %p\n", material);
	if (material->type != MATERIAL_TYPE_LAMBERTIAN) fprintf(stderr, "Material is not lambertian but %d\n", material->type);

	lambertian* plambertian = (lambertian*)material;
	free(plambertian);
}

bool lambertian_scatter_test(color3* albedo, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered) {
	vec3 temp0 = vec3_random_unit_vector();
	vec3 scatter_direction = vec3_add(&rec->normal, &temp0);

	if (vec3_near_zero(&scatter_direction))
		scatter_direction = rec->normal;

	ray temp1 = { rec->p, scatter_direction };
	*scattered = temp1;
	attenuation = albedo;

	return true;
}
