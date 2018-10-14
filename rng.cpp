/**
 * @file rng.cpp
 */

#include <cfloat>
#include <cmath>
#include <cstdlib>

#include <rng.h>

static const double ALMOST_ONE = 1 - DBL_EPSILON;

double frng(double min, double max)
{
    // First, generate base integer.
    double scale = max - min;
    double int_norm = (double)rand() / (double)RAND_MAX;
    double integer = floor(min + int_norm * scale);

    // Next, generate fractional component.
    double frac_norm = (double)rand() / (double)RAND_MAX;
    double frac = (double)(frac_norm * ALMOST_ONE);

    return integer + frac;
}

int rng(int min, int max)
{
    double scale = max - min + 1;
    double normalized = (double)rand() / (double)RAND_MAX;
    double val = min + (normalized * scale);
    return (int) floor(val);
}

int flip()
{
    return rng(0, 1);
}

int roll(int times, int sides, int modifier)
{
    int sum = 0;

    for (int i = 0; i < times; i++)
    {
        sum += rng(1, sides);
    }

    return sum + modifier;
}
