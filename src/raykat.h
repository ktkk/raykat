#ifndef RAYKAT_H
#define RAYKAT_H

/* STD */
#include <stdbool.h>
#include <math.h>

/* CONSTANTS */
#ifdef M_PI
#define PI M_PI
#else
#define PI (double)3.14159265358979323846
#endif
// INFINITY defined in math.h

/* UTILITY FUNCTIONS AND MACROS*/
#define DEG_TO_RAD(deg) (((deg) * PI) / 180.0)

/* HEADERS */
#include "vec3.h"
#include "ray.h"

#endif //RAYKAT_H
