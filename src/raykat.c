#include <stdio.h>

#define IMG_WIDTH 256
#define IMG_HEIGHT 256

#define CONVERT_TO_INT(name) i##name = (int)(255.999 * name)

int main() {
	printf("P3\n%d %d\n255\n", IMG_WIDTH, IMG_HEIGHT); /* PPM header:
							      P3 means colors are in ascii
							      followed by width and height */
	for (int i = IMG_HEIGHT - 1; i >= 0; --i) {
		fprintf(stderr, "\rScanlines remaining: %d", i);
		fflush(stderr);

		for (int j = 0; j < IMG_WIDTH; ++j) {
			double r, g, b;
			int ir, ig, ib;

			r = (double)j / (IMG_WIDTH - 1);
			g = (double)i / (IMG_HEIGHT - 1);
			b = 0.25;

			CONVERT_TO_INT(r);
			CONVERT_TO_INT(g);
			CONVERT_TO_INT(b);

			printf("%d %d %d\n", ir, ig, ib);
		}
	}

	fprintf(stderr, "\nDone.\n");
}
