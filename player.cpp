/**
 * @file player.cpp
 */

#include "actor.h"
#include "inventory.h"
#include "item.h"
#include "player.h"

Player::Player()
{
	// Initialize stats.
	level = 1;
	max_hp = 10;
	hp = max_hp;
	
	// Initialize attributes.
	atk = 1;
	def = 1;
}

/// @note Stub.
void attack(Actor& target)
{
	// Calculate damage.
	int damage = 2;
}
