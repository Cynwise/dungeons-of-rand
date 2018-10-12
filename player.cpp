/**
 * @file player.cpp
 */

#include <iostream>

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

Player* Player::clone()
{
	Player* tmp = new Player;
	*tmp = *this;
	return tmp;
}

void Player::attack(Actor& target)
{
	int damage = roll(1, level + 2, 0);
	
	target.hurt(damage);
	
	std::cout << "You deal " << damage << " damage to ";
	std::cout << target.get_name() << "!\n";
	std::cout << "Its current health is " << target.get_hp() << ".\n\n";
}

void Player::hurt(int damage)
{
	hp -= damage;
	
	std::cout << "It deals " << damage << " damage to you!\n";
	std::cout << "Your current health is " << hp << ".\n\n";
}
