#ifndef SCENE_H
#define SCENE_H

#include "hittable_list.h"

typedef enum {
	SCENE_SPHERES,
	SCENE_TRIS,
	SCENE_OBJ,
	SCENE_RANDOM,
} scene_type;

hittable_list* create_scene(scene_type type);
void cleanup_scene(hittable_list* scene);

#endif //SCENE_H
