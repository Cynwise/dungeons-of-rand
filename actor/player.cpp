/**
 * @file player.cpp
 */

#include <cassert>
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

    dodge = false;
}

Player* Player::clone()
{
    Player* tmp = new Player;
    *tmp = *this;
    return tmp;
}

void Player::attack(Actor& target)
{
    std::string response = "";

    // Prompt user to either attack or dodge.
    std::cout << "[A]ttack or [D]odge?\n\n> ";
    while (1)
    {
        std::getline(std::cin, response);

        // Verify player input.
        if
        (
            response != "A" &&
            response != "a" &&
            response != "D" &&
            response != "d"
        )
        {
            // Invalid input.
            std::cout << "Enter \"a\" or \"d\"\n\n> ";
        }
        else
        {
            // Valid input.
            break;
        }
    }
    std::cout << std::endl;

    if (response == "d" || response == "D")
    {
        int chance = roll(1, 6);

        // 2/3 chance of success.
        if (chance > 2)
        {
            dodge = true;
        }

        return;
    }
    // Else, attack.

    int atk = calc_atk();
    int damage = roll(1, atk);

    int net_damage = target.hurt(damage);

    std::cout << "You deal " << net_damage << " damage to the ";
    std::cout << target.get_name() << ".\n";
    std::cout << "Its current health is " << target.get_hp() << ".\n\n";
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
    def = roll(1, def) - 1;
    def *= 0.5;

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
