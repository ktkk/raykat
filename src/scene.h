#ifndef SCENE_H
#define SCENE_H

#include "hittable_list.h"

typedef enum {
	SCENE_SPHERES,
	SCENE_TRIS,
} scene;

hittable_list create_scene(scene scene_type);

#endif //SCENE_H
