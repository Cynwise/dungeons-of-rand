/**
 * @file player.h
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"

class Player : public Actor
{
public:

	Player();
	
	Player* clone();
	
	void attack(Actor& target);
	
	void hurt(int damage);
};

#endif // PLAYER_H
