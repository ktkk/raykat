#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#include "vec3.h"

#define CONVERT_COMPONENT(name) (int)(255.999 * name)

void write_color(FILE* stream, color3 color);

#endif //COLOR_H
