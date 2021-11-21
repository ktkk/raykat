#ifndef PIXEL_H
#define PIXEL_H

#include <stdbool.h>
#include <stdint.h>

#include "vec3.h"

typedef uint32_t hexcolor32;

typedef struct {
	int x, y;

	// TODO(ktkk): Adding any more members to this struct causes a segfault. Figure out why.
	//color3 color_rgb;
	//hexcolor32 color_hex;
	//unsigned int color_hex;

	//bool rendered;
} pixel;

#endif //PIXEL_H
