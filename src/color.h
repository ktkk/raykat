#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#include "vec3.h"

#define CONVERT_COMPONENT(name) (int)(255.999 * name)

void write_color(FILE* stream, const color3* color, const unsigned int samples_per_pixel);

#endif //COLOR_H
