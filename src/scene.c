#include <stdlib.h>
#include <stdio.h>
#include "scene.h"

#include "raykat.h"

#include "sphere.h"
#include "triangle.h"
#include "objloader.h"

#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

#include "vec3.h"

static hittable_list* create_sphere_scene();
static hittable_list* create_tris_scene();
static hittable_list* create_obj_scene();
static hittable_list* create_random_scene();

hittable_list* create_scene(const scene_type type) {
	switch (type) {
	case SCENE_SPHERES:
		return create_sphere_scene();
		break;
	case SCENE_TRIS:
		return create_tris_scene();
		break;
	case SCENE_OBJ:
		return create_obj_scene();
		break;
	case SCENE_RANDOM:
		return create_random_scene();
		break;
	default:
		fprintf(stderr, "Unknown scene type %d. Loading SCENE_SPHERES instead", type);
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
	const point3 center0 = {{ 0, -1, 0 }};
	const point3 center1 = {{ 0, -1, -100.5 }};
	const point3 center2 = {{ -2, -1, 0 }};
	const point3 center3 = {{ 2, -1, 0 }};

	const color3 ground_color = {{ 0.8, 0.8, 0.0 }};
	material* material_ground = lambertian_new(&ground_color);
	const color3 center_color = {{ 0.1, 0.2, 0.5 }};
	material* material_center = lambertian_new(&center_color);
	material* material_left_1 = dielectric_new(1.5);
	material* material_left_2 = dielectric_new(1.5);
	const color3 right_color = {{ 0.8, 0.6, 0.2 }};
	material* material_right = metal_new(&right_color, 0.0);

	hittable_list_add(scene, sphere_new(&center1, 100, material_ground));
	hittable_list_add(scene, sphere_new(&center0, 0.5, material_center));
	hittable_list_add(scene, sphere_new(&center2, 0.5, material_left_1));
	hittable_list_add(scene, sphere_new(&center2, -0.4, material_left_2));
	hittable_list_add(scene, sphere_new(&center3, 0.5, material_right));

	return scene;
}

hittable_list* create_tris_scene() {
	hittable_list* scene = hittable_list_init(12);

	/* 8 points to represent 12 tris of the cube */
	const point3 p0 = {{ 0.5, -0.5, -0.5 }}, p1 = {{ -0.5, -0.5, 0.5 }}, p2 = {{ -0.5, -0.5, -0.5 }},
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

	const color3 ground_color = {{ 0.8, 0.8, 0.0 }};
	material* material_ground = lambertian_new(&ground_color);

	const point3 center1 = {{ 0, -1, -100.5 }};
	hittable_list_add(scene, sphere_new(&center1, 100, material_ground));

	return scene;
}

hittable_list* create_obj_scene() {
	hittable_list* scene = hittable_list_init(500);

	int ntris = 0;
	obj_triangle* triangles = objloader_get_tris("test/monkey.obj", &ntris);

	for (int i = 0; i < ntris; ++i) {
		hittable_list_add(scene, triangle_new(&triangles[i].p0, &triangles[i].p1, &triangles[i].p2));
	}

	free(triangles);

	const color3 ground_color = {{ 0.8, 0.8, 0.0 }};
	material* material_ground = lambertian_new(&ground_color);

	const point3 center1 = {{ 0, -1, -100.5 }};
	hittable_list_add(scene, sphere_new(&center1, 100, material_ground));

	return scene;
}

hittable_list* create_random_scene() {
	hittable_list* scene = hittable_list_init(500);

#define SMALL_RADIUS 0.2
#define BIG_RADIUS 1.0

#define GLASS_IR 1.5

	const color3 ground_color = {{ 0.5, 0.5, 0.5 }};
	material* material_ground = lambertian_new(&ground_color);

	const point3 ground_center = {{ 0, -1000, 0 }};
	hittable_list_add(scene, sphere_new(&ground_center, 1000, material_ground));

	for (int a = -11; a < 11; ++a) {
		for (int b = -11; b < 11; ++b) {
			const double choose_mat = RAND_DOUBLE;
			const point3 center = {{ a + 0.9 * RAND_DOUBLE, 0.2, b + 0.9 * RAND_DOUBLE }};

			const point3 temp0 = {{ 4, 0.2, 0 }};
			const vec3 temp1 = vec3_sub(&center, &temp0);
			if (vec3_length(&temp1) > 0.9) {
				material* sphere_material;

				if (choose_mat < 0.8) {
					/* Diffuse */
					const color3 rand0 = vec3_random();
					const color3 rand1 = vec3_random();
					const color3 albedo = vec3_multiply_vectors(&rand0, &rand1);

					sphere_material = lambertian_new(&albedo);
					hittable_list_add(scene, sphere_new(&center, SMALL_RADIUS, sphere_material));
				}
				else if (choose_mat < 0.95) {
					/* Metal */
					const color3 albedo = vec3_random_range(0.5, 1);
					double fuzz = RAND_DOUBLE_RANGE(0, 0.5);

					sphere_material = metal_new(&albedo, fuzz);
					hittable_list_add(scene, sphere_new(&center, SMALL_RADIUS, sphere_material));
				}
				else {
					/* Glass */
					sphere_material = dielectric_new(GLASS_IR);
					hittable_list_add(scene, sphere_new(&center, SMALL_RADIUS, sphere_material));
				}
			}
		}
	}

	material* material1 = dielectric_new(GLASS_IR);
	const point3 center1 = {{ 0, 1, 0 }};
	hittable_list_add(scene, sphere_new(&center1, BIG_RADIUS, material1));

	const color3 color2 = {{ 0.4, 0.2, 0.1 }};
	material* material2 = lambertian_new(&color2);
	const point3 center2 = {{ -4, 1, 0 }};
	hittable_list_add(scene, sphere_new(&center2, BIG_RADIUS, material2));

	const color3 color3 = {{ 0.7, 0.6, 0.5 }};
	material* material3 = metal_new(&color3, 0.0);
	const point3 center3 = {{ 4, 1, 0 }};
	hittable_list_add(scene, sphere_new(&center3, BIG_RADIUS, material3));

	return scene;
}
