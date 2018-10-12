/**
 * @file player.h
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"

class Player : Actor
{
public:

	Player();
	
	/// Make attack against another actor.
	void attack(Actor& target);
	
	/// Receive damage.
	void hurt(int damage);
	
	/// Increase HP.
	void heal(int points);
};

#endif // PLAYER_H
