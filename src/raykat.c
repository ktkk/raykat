#include <stdio.h>

#include "vec3.h"
#include "color.h"

#define IMG_WIDTH 256
#define IMG_HEIGHT 256

int main() {
	printf("P3\n%d %d\n255\n", IMG_WIDTH, IMG_HEIGHT); /* PPM header:
							      P3 means colors are in ascii
							      followed by width and height */
	for (int i = IMG_HEIGHT - 1; i >= 0; --i) {
		fprintf(stderr, "\rScanlines remaining: %d", i);
		fflush(stderr);

		for (int j = 0; j < IMG_WIDTH; ++j) {
			color3 pixel_color;
			pixel_color.x = (double)j / (IMG_WIDTH - 1);
			pixel_color.y = (double)i / (IMG_HEIGHT - 1);
			pixel_color.z = 0.25;

			write_color(stdout, pixel_color);
		}
	}

	fprintf(stderr, "\nDone.\n");
}
