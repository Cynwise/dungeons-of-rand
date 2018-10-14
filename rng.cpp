/**
 * @file rng.cpp
 */

#include <cstdlib>

#include <rng.h>

double frng(double min, double max)
{
    double scale = max - min + 1;
    double normalized = (double)rand() / (double)RAND_MAX;
    return min + (normalized * scale);
}

int rng(int min, int max)
{
    return frng((double)min, (double)max);
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
