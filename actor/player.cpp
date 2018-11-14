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
#include <module.h>
#include <rng.h>

Player::Player()
{
    static bool constructed = false;

    if (constructed == true)
    {
        std::cerr << "Error: Attempt to create multiple player instances.\n";
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

    // Pick an attack type.
    Attack_Type* this_attack;
    if (attack_list.empty())
    {
        this_attack = attack_map["attack"];
    }
    else
    {
        int entry = rng(0, attack_list.size() - 1);
        const std::string& attack_name = attack_list[entry];
        this_attack = attack_map[attack_name];
    }

    // Calculate damage.
    int atk = calc_atk();
    int damage = roll(1, atk) + this_attack->calc_atk();

    int net_damage = target.hurt(damage);

    // Report results.
    if (net_damage > 0)
    {
        this_attack->print_attack(*this, target, net_damage);
    }
    else
    {
        std::cout << "You attempt to attack the " << target.get_name();
        std::cout << "but it dodges.\n\n";
    }
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

void Player::print_status()
{
    // Report player HP.
    std::cout << "Your current health is " << hp << "/" << max_hp << ".\n";
}
