#include <stdio.h>
#include "scene.h"

#include "vec3.h"

#include "sphere.h"
#include "triangle.h"

static hittable_list* create_sphere_scene();
static hittable_list* create_tris_scene();

hittable_list* create_scene(scene scene_type) {
	switch (scene_type) {
	case SCENE_SPHERES:
		return create_sphere_scene();
		break;
	case SCENE_TRIS:
		return create_tris_scene();
		break;
	default:
		fprintf(stderr, "Unknown scene type %d. Loading SCENE_SPHERES instead", scene_type);
		return create_sphere_scene();
		break;
	}
}

void cleanup_scene(hittable_list* scene) {
	hittable_list_cleanup(scene);
}

hittable_list* create_sphere_scene() {
	hittable_list* scene = hittable_list_init(4);

	/* Sphere centers */
	point3 center0 = {{ 0, -1, 0 }};
	point3 center1 = {{ 0, -1, -100.5 }};
	point3 center2 = {{ -2, -1, 0 }};
	point3 center3 = {{ 2, -1, 0 }};

	hittable_list_add(scene, sphere_new(&center0, 0.5));
	hittable_list_add(scene, sphere_new(&center1, 100));
	hittable_list_add(scene, sphere_new(&center2, 0.5));
	hittable_list_add(scene, sphere_new(&center3, 0.5));

	return scene;
}

hittable_list* create_tris_scene() {
	hittable_list* scene = hittable_list_init(12);

	/* 8 points to represent 12 tris of the cube */
	point3 p0 = {{ 0.5, -0.5, -0.5 }}, p1 = {{ -0.5, -0.5, 0.5 }}, p2 = {{ -0.5, -0.5, -0.5 }},
	       p3 = {{ 0.5, -0.5, 0.5 }}, p4 = {{ 0.5, -1.5, -0.5 }}, p5 = {{ 0.5, -1.5, 0.5 }},
	       p6 = {{ -0.5, -1.5, 0.5 }}, p7 = {{ -0.5, -1.5, -0.5 }};
	// TODO(katkak): Optimize this.

	/* Create tris from these points */
	/* Front */
	hittable_list_add(scene, triangle_new(&p0, &p1, &p2));
	hittable_list_add(scene, triangle_new(&p0, &p1, &p3));
	/* Left */
	hittable_list_add(scene, triangle_new(&p4, &p3, &p0));
	hittable_list_add(scene, triangle_new(&p4, &p3, &p5));
	/* Top */
	hittable_list_add(scene, triangle_new(&p3, &p6, &p1));
	hittable_list_add(scene, triangle_new(&p3, &p6, &p5));
	/* Right */
	hittable_list_add(scene, triangle_new(&p2, &p6, &p7));
	hittable_list_add(scene, triangle_new(&p2, &p6, &p1));
	/* Back */
	hittable_list_add(scene, triangle_new(&p7, &p5, &p4));
	hittable_list_add(scene, triangle_new(&p7, &p5, &p6));
	/* Bottom */
	hittable_list_add(scene, triangle_new(&p4, &p2, &p7));
	hittable_list_add(scene, triangle_new(&p4, &p2, &p0));

	point3 center1 = {{ 0, -1, -100.5 }};
	hittable_list_add(scene, sphere_new(&center1, 100));

	return scene;
}
