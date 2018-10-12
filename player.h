/**
 * @file player.h
 * @brief Actor that represents the player character. Also declares
 * the global Player instance.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"

/// Actor that represents the player character.
class Player : public Actor
{
public:

	Player();

	Player* clone();

	void attack(Actor& target);

	int hurt(int damage);
};

/// Global player instance.
extern Player player;

#endif // PLAYER_H
