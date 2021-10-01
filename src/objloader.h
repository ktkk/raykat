#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "vec3.h"

/*
 * Blender obj export settings:
 * Selection only (for now),
 * Forward: Y Forward,
 * Up: Z Up,
 * Do not write normals/UVs/material,
 * Triangulate faces
 */

typedef struct {
	point3 p0;
	point3 p1;
	point3 p2;
} obj_triangle;

obj_triangle* objloader_get_tris(char* filename, int* size);
void objloader_cleanup();

#endif //OBJLOADER_H
