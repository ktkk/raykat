#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "material_shared.h"

typedef struct {
	material base;

	f64 ir;
} dielectric;

material* dielectric_new(const f64 index_of_refraction);
void dielectric_delete(const material* material);

#endif //DIELECTRIC_H
