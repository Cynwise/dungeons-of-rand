/**
 * @file player.cpp
 */

#include <cassert>
#include <cstdlib>
#include <iostream>

#include <actor.h>
#include <actor_module.h>
#include <actor/player.h>
#include <attack_type.h>
#include <item/armor.h>
#include <item/weapon.h>
#include <module.h>
#include <rng.h>

Player::Player()
{
    static bool constructed = false;

    if (constructed == true)
    {
        std::cerr << "Error: Attempt to create multiple player instances.\n\n";
        std::exit(1);
    }
    else
    {
        constructed = true;
    }
}

Player* Player::clone()
{
    Player* tmp = new Player;
    *tmp = *this;
    return tmp;
}

Player& Player::get_instance()
{
    static Player instance;
    static bool constructed = false;

    // Construct the instance upon the first call.
    if (constructed == false)
    {
        // Get stats from default player module.
        *((Actor*)&instance) = Actor("player");

        // Overrides.
        instance.dodge = false;

        constructed = true;
    }

    return instance;
}

int Player::hurt(int damage)
{
    // Sanity check. Damage cannot be negative.
    assert(damage >= 0);

    // Check if we are dodging.
    if (dodge == true)
    {
        dodge = false;

        return 0;
    }

    int hp_before = hp;

    // Calculate defense. Net def = (1d(def)-1)/2
    int def = calc_def();
    if (armor != nullptr)
    {
        def += armor->get_def();
    }
    def = roll(2, def) / 2 - 1;

    // Apply defense to damage taken.
    damage -= def;

    // Prevent negative damage.
    if (damage < 0)
    {
        damage = 0;
    }

    // Take damage.
    hp -= damage;

    // Prevent negative health.
    if (hp < 0)
    {
        hp = 0;
    }

    // Return net damage.
    return hp_before - hp;
}

void Player::print_status()
{
    // Report player HP.
    std::cout << "Your current health is " << hp << "/" << max_hp << ".\n\n";
}
