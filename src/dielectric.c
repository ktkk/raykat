#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "raykat.h"

#include "dielectric.h"
#include "hittable.h"
#include "vec3.h"

static bool dielectric_scatter(material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered);

material* dielectric_new(double index_of_refraction) {
	dielectric* pdielectric = (dielectric*)calloc(1, sizeof(*pdielectric));
	if (pdielectric == NULL) fprintf(stderr, "Calloc failed: %p\n", pdielectric);

	material_init(&pdielectric->base, MATERIAL_TYPE_DIELECTRIC, dielectric_scatter, dielectric_delete);
	pdielectric->ir = index_of_refraction;

	return (material*)pdielectric;
}

static double reflectance(double cosine, double ref_idx) {
	/* Use Schlick's approximation for reflectance */
	double r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;

	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool dielectric_scatter(material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered) {
	if (material == NULL) fprintf(stderr, "Material is NULL: %p\n", material);
	if (material->type != MATERIAL_TYPE_DIELECTRIC) fprintf(stderr, "Material is not dielectric but %d\n", material->type);

	dielectric* pdielectric = (dielectric*)material;

	color3 white = {{ 1.0, 1.0, 1.0 }};
	*attenuation = white;
	double refraction_ratio = rec->front_face ? (1.0 / pdielectric->ir) : pdielectric->ir;

	vec3 unit_direction = vec3_norm(&r_in->direction);

	vec3 temp0 = vec3_invert(&unit_direction);
	double cos_theta = fmin(vec3_dotprod(&temp0, &rec->normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.0;
	vec3 direction;

	if (cannot_refract || reflectance(cos_theta, refraction_ratio) > RAND_DOUBLE)
		direction = vec3_reflect(&unit_direction, &rec->normal);
	else
		direction = vec3_refract(&unit_direction, &rec->normal, refraction_ratio);

	ray temp1 = { rec->p, direction };
	*scattered = temp1;

	return true;
}

void dielectric_delete(material* material) {
	if (material == NULL) fprintf(stderr, "Material is NULL: %p\n", material);
	if (material->type != MATERIAL_TYPE_DIELECTRIC) fprintf(stderr, "Material is not dielectric but %d\n", material->type);

	dielectric* pdielectric = (dielectric*)material;
	free(pdielectric);
}
