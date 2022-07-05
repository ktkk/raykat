#ifndef RAYKAT_H
#define RAYKAT_H

#include "types.h"

/* STD */
#include <math.h>
#include <stdlib.h>

/* CONSTANTS */
#ifdef M_PI
#define PI M_PI
#else
#define PI (f64)3.14159265358979323846
#endif
// INFINITY defined in math.h

/* UTILITY FUNCTIONS AND MACROS*/
#define DEG_TO_RAD(deg) (((deg) * PI) / 180.0)
#define RAND_DOUBLE (rand() / (RAND_MAX + 1.0))
#define RAND_DOUBLE_RANGE(min, max) ((max - min) * RAND_DOUBLE + min)
static inline f64 clamp(const f64 x, const f64 min, const f64 max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

#endif //RAYKAT_H
