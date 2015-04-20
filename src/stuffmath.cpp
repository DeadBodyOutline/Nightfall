#include "stuffmath.h"

// Code based on the following sources:
// http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method
// http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Approximations_that_depend_on_IEEE_representation
float stuffSqrt(const float number)
{
    union {
        int i;
        float x;
    } u;

    u.x = number;
    u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

    u.x = u.x + number / u.x;
    u.x = 0.25f * u.x + number / u.x;

    return u.x;
}

// distance on a vector
float stuffDistance(const float x, const float y)
{
    return stuffSqrt(x * x + y * y);
}

float stuffDistanceF(const float x1, const float y1, const float x2, const float y2)
{
    float p = x1 - x2;
    float q = y1 - y2;

    return stuffDistance(p, q);
}

// compare distances between two points (p1 and p2)
// we don't need sqrt to just compare distances
// 1 if p1 > p2, -1 if p1 < p2 and 0 if p1 == p2
int stuffCompareDistance(const float x1, const float y1, const float x2, const float y2)
{
    float d1 = x1 * x1 + y1 * y1;
    float d2 = x2 * x2 + y2 * y2;

    int ret = 0;

    if (d1 > d2)
        ret = 1;
    else if (d1 < d2)
        ret = -1;

    return ret;
}
