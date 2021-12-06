#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"
#include "ray.h"

struct hit_record;

typedef struct material_s material;

void material_delete(material* material);
bool material_scatter(material* material, const hit_record* rec, color3* attenuation, ray* scattered);

#endif //MATERIAL_H
