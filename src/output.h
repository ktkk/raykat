#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#ifdef PREVIEW
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>

#define PREVIEW_BG 0x0E0870

typedef uint32_t pixel32;

static pixel32* pixels;
#endif

#include "raykat.h"

#define CONVERT_COMPONENT(name) (int)(255.999 * name)
#define RGB_TO_HEX(r, g, b) (CONVERT_COMPONENT(r) << (8 * 2)) | \
							(CONVERT_COMPONENT(g) << (8 * 1)) | \
							(CONVERT_COMPONENT(b) << (8 * 0))

#ifdef PREVIEW
bool init_preview_window(int width, int height);

void write_color_to_preview_window(color3* color, int samples_per_pixel);
void show_preview_window();
#endif
void write_color_to_file(FILE* stream, color3* color, int samples_per_pixel);

#endif //OUTPUT_H
