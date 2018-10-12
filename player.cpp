/**
 * @file player.cpp
 */

#include <cassert>

#include "actor.h"
#include "inventory.h"
#include "item.h"
#include "player.h"
#include "rng.h"

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
void Player::attack(Actor& target)
{
	// Calculate damage.
	int damage = roll(1, atk, 0);
	
	target.hurt(damage);
}

/// @note Stub.
void Player::hurt(int damage)
{
	// Sanity check. Damage cannot be negative.
	assert(damage >= 0);
	
	// Account for defense.
	damage -= def;
	
	// Prevent negative damage.
	if (damage < 0)
	{
		damage = 0;
	}
	
	hp -= damage;
	
	// Prevent negative health.
	if (hp < 0)
	{
		hp = 0;
	}
}

/// @note Stub.
void Player::heal(int points)
{
	// Sanity check. Healing cannot be negative.
	assert(points >= 0);
	
	hp += points;
	
	// Respect hp limits.
	if (hp > max_hp)
	{
		hp = max_hp;
	}
}
