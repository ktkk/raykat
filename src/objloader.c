#include <stdio.h>
#include <string.h>
#include "objloader.h"

#include "vec3.h"

#define LINE_LEN 512

static bool check_obj(char* filename) {
	char* ext;
	if ((ext = strrchr(filename, '.')) != NULL) {
		return strcmp(ext, ".obj") == 0;
	}

	return false;
}

triangle* objloader_get_tris(char* filename) {
	if (!check_obj(filename)) {
		fprintf(stderr, "File \'%s\' is not an obj.\n", filename);
		return NULL;
	}

	int points;
	point3* pointarr;
	int triangles;
	triangle* trianglearr;

	char* vertex_token = "v ";
	char* face_token = "f ";

	FILE* fp;

	if ((fp = fopen(filename, "r")) == NULL){
		fprintf(stderr, "Opening file failed.\n");
		return NULL;
	}

	// TODO(katkak): Implement pattern searching and point/triangle parsing
	//char line[LINE_LEN];
	//while (fgets(line, LINE_LEN, fp)) {
	//	if (strstr(line, vertex_token)) {
	//		++points;
	//	}
	//	else if (strstr(line, face_token)) {
	//		++triangles;
	//	}
	//}

	fclose(fp);

	fprintf(stderr, "Nr of points: %d\nNr of triangles: %d\n", points, triangles);

	return NULL;
}
