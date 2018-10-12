/**
 * @file rng.cpp
 */

#include <cstdlib>

#include "rng.h"

int rng(int min, int max)
{
	return min + rand() % (1 + max - min);
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
