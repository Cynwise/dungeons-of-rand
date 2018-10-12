/**
 * @file player.cpp
 */

#include <iostream>

#include "player.h"
#include "rng.h"

/// Construct the global player instance.
Player player;

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

Player* Player::clone()
{
	Player* tmp = new Player;
	*tmp = *this;
	return tmp;
}

void Player::attack(Actor& target)
{
	int damage = roll(1, level + 2, 0);
	
	int net_damage = target.hurt(damage);
	
	std::cout << "You deal " << net_damage << " damage to the ";
	std::cout << target.get_name() << ".\n";
	std::cout << "Its current health is " << target.get_hp() << ".\n\n";
}

int Player::hurt(int damage)
{
	int hp_before = hp;
	
	hp -= damage;
	
	// Prevent negative health.
	if (hp < 0)
	{
		hp = 0;
	}
	
	int net_damage = hp_before - hp;
	
	std::cout << "It deals " << net_damage << " damage to you.\n";
	std::cout << "Your current health is " << hp << ".\n\n";
	
	return net_damage;
}
