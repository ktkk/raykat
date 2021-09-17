#include "color.h"

void write_color(FILE* stream, color3* color) {
	/* Write out the translated [0, 255] value of each color component */
	fprintf(stream, "%d %d %d\n", CONVERT_COMPONENT(color->r), CONVERT_COMPONENT(color->g), CONVERT_COMPONENT(color->b));
}
