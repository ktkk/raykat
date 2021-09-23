#include <math.h>
#include "color.h"

void write_color(FILE* stream, color3* color, int samples_per_pixel) {
	double scale = 1.0 / samples_per_pixel;
	double r = sqrt(scale * color->r);
	double g = sqrt(scale * color->g);
	double b = sqrt(scale * color->b);

	/* Write out the translated [0, 255] value of each color component */
	fprintf(stream, "%d %d %d\n",
			CONVERT_COMPONENT(clamp(r, 0.0, 0.999)),
			CONVERT_COMPONENT(clamp(g, 0.0, 0.999)),
			CONVERT_COMPONENT(clamp(b, 0.0, 0.999))
		);
}
