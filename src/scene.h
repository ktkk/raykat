#ifndef SCENE_H
#define SCENE_H

#include "hittable_list.h"

typedef enum {
	SCENE_SPHERES,
	SCENE_TRIS,
} scene;

hittable_list create_scene(scene scene_type);
void cleanup_scene(hittable_list* scene);

#endif //SCENE_H
