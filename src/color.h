#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#include "raykat.h"

#define CONVERT_COMPONENT(name) (int)(255.999 * name)

void write_color(FILE* stream, color3* color, int samples_per_pixel);

#endif //COLOR_H
