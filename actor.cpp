/**
 * @file actor.cpp
 */

#include <string>

#include "actor.h"

void Actor::level_up()
{
	xp = 0;
	level++;
}

const std::string& Actor::get_name()
{
	return name;
}

void Actor::set_name(const std::string& s)
{
	name = s;
}

int Actor::get_hp()
{
	return hp;
}

void Actor::set_hp(int val)
{
	hp = val;
}

int Actor::get_level()
{
	return level;
}

void Actor::set_level(int val)
{
	level = val;
}
