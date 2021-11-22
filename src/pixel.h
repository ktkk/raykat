#ifndef PIXEL_H
#define PIXEL_H

#include <stdbool.h>
#include <stdint.h>

#include "vec3.h"

typedef uint32_t hexcolor32;

typedef struct pixel {
	color3 color_rgb;
	hexcolor32 color_hex;

	bool rendered;
} pixel;

#endif //PIXEL_H
