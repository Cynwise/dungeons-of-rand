/**
 * @file player.cpp
 */

#include <iostream>

#include <actor/player.h>
#include <rng.h>

/// Construct the global player instance.
Player player;

Player::Player()
{
    // Initialize stats.
    level = 1;
    max_hp = 20;
    hp = max_hp;

    // Initialize attributes.
    strength = 5;
    fortitude = 5;
}

Player* Player::clone()
{
    Player* tmp = new Player;
    *tmp = *this;
    return tmp;
}

void Player::attack(Actor& target)
{
    int atk = calc_atk();
    int damage = roll(1, atk);

    int net_damage = target.hurt(damage);

    std::cout << "You deal " << net_damage << " damage to the ";
    std::cout << target.get_name() << ".\n";
    std::cout << "Its current health is " << target.get_hp() << ".\n\n";
}
