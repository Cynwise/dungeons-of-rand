/**
 * @file actor.cpp
 */

#include <cassert>
#include <string>

#include "actor.h"
#include "inventory.h"
#include "rng.h"

Actor::Actor()
{
	// Initialize main stats.
	name = "[GENERIC ACTOR]";
	level = 0;
	xp = 0;
	max_hp = 0;
	hp = 0;
	
	// Initialize attributes.
	atk = 0;
	atk = 0;
	
	// Initialize possessions.
	items = new Inventory;
	weapon = nullptr;
	armor = nullptr;
}

void Actor::attack(Actor& target)
{
	// Calculate damage.
	int damage = roll(1, level, 0);
	
	target.hurt(damage);
}

void Actor::hurt(int damage)
{
	// Sanity check. Damage cannot be negative.
	assert(damage >= 0);
	
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

void Actor::heal(int points)
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

void Actor::level_up()
{
	xp = 0;
	level++;
}

std::string Actor::get_name() const
{
	return name;
}

void Actor::set_name(const std::string& s)
{
	name = s;
}

int Actor::get_hp() const
{
	return hp;
}

void Actor::set_hp(int val)
{
	hp = val;
}

int Actor::get_level() const
{
	return level;
}

void Actor::set_level(int val)
{
	level = val;
}
