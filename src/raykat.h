#ifndef RAYKAT_H
#define RAYKAT_H

/* STD */
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

/* CONSTANTS */
#ifdef M_PI
#define PI M_PI
#else
#define PI (double)3.14159265358979323846
#endif
// INFINITY defined in math.h

/* UTILITY FUNCTIONS AND MACROS*/
#define DEG_TO_RAD(deg) (((deg) * PI) / 180.0)
#define RAND_DOUBLE (rand() / (RAND_MAX + 1.0))
#define RAND_DOUBLE_RANGE(min, max) ((max - min) * RAND_DOUBLE + min)
static inline double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

/* HEADERS */
#include "vec3.h"
#include "ray.h"

#endif //RAYKAT_H
