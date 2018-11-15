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

void Player::attack(Actor& target)
{
    // Pick an attack type.
    std::string attack_name;
    if (has_weapon())
    {
        if (!weapon->attack_list.empty())
        {
            int entry = rng(0, weapon->attack_list.size() - 1);
            attack_name = weapon->attack_list[entry];
        }
        else
        {
            attack_name = "attack";
        }
    }
    else
    {
        if (attack_list.empty())
        {
            attack_name = "attack";
        }
        else
        {
            int entry = rng(0, attack_list.size() - 1);
            attack_name = attack_list[entry];
        }
    }

    attack(target, attack_name);
}

void Player::attack(Actor& target, const std::string& attack_name)
{
    int atk = 0;
    int damage = 0;

    // Get attack type.
    Attack_Type* this_attack = attack_map[attack_name];

    // Check if weapon attack or intrinsic attack.
    bool weapon_attack = false;
    if (has_weapon())
    {
        for (auto& attack_it : weapon->attack_list)
        {
            if (attack_name == attack_it)
            {
                weapon_attack = true;
                break;
            }
        }
    }

    // Calculate damage.
    if (weapon_attack == true)
    {
        atk = calc_atk() + weapon->get_atk() + this_attack->calc_atk();
    }
    else
    {
        atk = calc_atk() + this_attack->calc_atk();
    }

    damage = roll(2, atk) / 2 + 1;
    int net_damage = target.hurt(damage);

    // Report results.
    if (net_damage > 0)
    {
        this_attack->print_attack(*this, target, net_damage);
    }
    else
    {
        std::cout << "You attempt to attack the " << target.get_name();
        std::cout << " but it dodges.\n\n";
    }
};

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
