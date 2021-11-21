#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#define __USE_MISC
#include <sys/mman.h>

#include "raykat.h"

#define PREVIEW_BG 0x0E0870

#define CONVERT_COMPONENT(name) (int)(255.999 * name)

#define RGB_TO_HEX(r, g, b) (CONVERT_COMPONENT(r) << (8 * 2)) | \
							(CONVERT_COMPONENT(g) << (8 * 1)) | \
							(CONVERT_COMPONENT(b) << (8 * 0))
#define HEX_TO_RGB(hex) (hex >> (8 * 2)) & 0xFF, \
						(hex >> (8 * 1)) & 0xFF, \
						(hex >> (8 * 0)) & 0xFF

void write_color_to_file(FILE* stream, color3* color, int samples_per_pixel);

#endif //OUTPUT_H
