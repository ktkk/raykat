#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "objloader.h"

#include "vec3.h"

#define LINE_LEN 512

static bool check_obj(const char* filename) {
	char* ext;
	if ((ext = strrchr(filename, '.')) != NULL) {
		return strcmp(ext, ".obj") == 0;
	}

	return false;
}

obj_triangle* objloader_get_tris(const char* filename, usize* size) {
	if (!check_obj(filename)) {
		fprintf(stderr, "File \'%s\' is not an obj.\n", filename);
		return NULL;
	}

	FILE* fp;

	if ((fp = fopen(filename, "r")) == NULL){
		fprintf(stderr, "Opening file failed.\n");
		return NULL;
	}

	char line_buf[LINE_LEN];

	usize npoints = 0;
	usize ntriangles = 0;
	/* Get nr of points and tris */
	while (fgets(line_buf, LINE_LEN, fp)) {
		if (line_buf[0] == 'v' && line_buf[1] == ' ')
			npoints++;
		else if (line_buf[0] == 'f' && line_buf[1] == ' ')
			ntriangles++;
	}

	*size = ntriangles;

	point3* pointarr = (point3*)calloc(npoints, sizeof(*pointarr));
	obj_triangle* trianglearr = (obj_triangle*)calloc(ntriangles, sizeof(*trianglearr));

	usize idx = 0;
	rewind(fp);
	while (fgets(line_buf, LINE_LEN, fp) && idx < npoints) {
		f64 x, y, z;
		if (sscanf(line_buf, "v %lf %lf %lf\n", &x, &y, &z)) {
			point3 p = {{ x, y, z }};
			pointarr[idx++] = p;
		}
	}

	idx = 0;
	rewind(fp);
	while (fgets(line_buf, LINE_LEN, fp)) {
		i32 p0, p1, p2;
		if (sscanf(line_buf, "f %d %d %d", &p0, &p1, &p2)) {
			obj_triangle triangle = { pointarr[p0 - 1], pointarr[p1 - 1], pointarr[p2 - 1] };
			trianglearr[idx++] = triangle;
		}
	}

	fclose(fp);
	free(pointarr);

	return trianglearr;
}
