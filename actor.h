/**
 * @file actor.h
 * @brief Base class for all creatures, including the player and any
 * NPCs.
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <string>

class Inventory;
class Item;

/// Generic base class for all NPCs.
class Actor
{
public:
	
	/// Make attack against another actor.
	virtual void attack(Actor& target) = 0;
	
	/// Receive damage.
	virtual void hurt(int damage) = 0;
	
	/// Increase HP.
	virtual void heal(int points) = 0;
	
	/// Levels up actor and zeros XP.
	void level_up();
	
	// Getters and setters.
	const std::string& get_name();
	void set_name(const std::string& s);
	int get_hp();
	void set_hp(int val);
	int get_level();
	void set_level(int val);
	
protected:

	std::string name;
	int level;
	int xp;
	int max_hp;
	int hp;
	
	// Attributes.
	int atk;
	int def;
	
	// Possessions.
	Inventory* items;
	Item* weapon;
	Item* armor;
};

#endif // ACTOR_H
