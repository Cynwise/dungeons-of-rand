/**
 * @file rat.h
 * @brief Simple enemy class.
 */

#ifndef RAT_H
#define RAT_H

#include <actor.h>

/// Simple enemy class.
class Rat : public Actor
{
public:

	Rat();

	Rat* clone();

	void attack(Actor& target);
};

#endif // RAT_H
