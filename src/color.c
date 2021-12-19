#include <math.h>
#include "color.h"

#include "raykat.h"

void write_color(FILE* stream, const color3* color, const unsigned int samples_per_pixel) {
	const double scale = 1.0 / samples_per_pixel;
	const double r = sqrt(scale * color->r);
	const double g = sqrt(scale * color->g);
	const double b = sqrt(scale * color->b);

	/* Write out the translated [0, 255] value of each color component */
	fprintf(stream, "%d %d %d\n",
			CONVERT_COMPONENT(clamp(r, 0.0, 0.999)),
			CONVERT_COMPONENT(clamp(g, 0.0, 0.999)),
			CONVERT_COMPONENT(clamp(b, 0.0, 0.999))
		);
}
