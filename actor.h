/**
 * @file actor.h
 * @brief Base class for all creatures, including the player and any
 * NPCs.
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <string>

class Armor;
class Inventory;
class Item;
class Weapon;

/// Generic base class for all NPCs.
class Actor
{
public:

	Actor();
	
	virtual Actor* clone() = 0;
	
	/// Make attack against another actor.
	virtual void attack(Actor& target);
	
	/// Receive damage.
	virtual void hurt(int damage);
	
	/// Increase HP.
	virtual void heal(int points);
	
	/// Levels up actor and zeros XP.
	void level_up();
	
	// Getters and setters.
	std::string get_name() const;
	void set_name(const std::string& s);
	int get_hp() const;
	void set_hp(int val);
	int get_level() const;
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
	Weapon* weapon;
	Armor* armor;
};

#endif // ACTOR_H
