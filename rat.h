/**
 * @file rat.h
 */

#ifndef RAT_H
#define RAT_H

#include "actor.h"

class Rat : public Actor
{
public:

	Rat();
	
	Rat* clone();
	
	void attack(Actor& target);
};

#endif // RAT_H
