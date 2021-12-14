#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdbool.h>

#include "vec3.h"
#include "ray.h"
#include "hit_record.h"

typedef struct material_s material;

void material_delete(material* material);
bool material_scatter(material* material, const ray* r_in, const hit_record* rec, color3* attenuation, ray* scattered);

#endif //MATERIAL_H
