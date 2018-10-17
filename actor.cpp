/**
 * @file actor.cpp
 * @brief Generic base class behaviors for Actors.
 */

#include <cassert>
#include <iostream>
#include <string>

#include <actor.h>
#include <actor/player.h>
#include <item/armor.h>
#include <item/weapon.h>
#include <inventory.h>
#include <rng.h>

Actor::Actor()
{
    // Initialize main stats.
    name = "[GENERIC ACTOR]";
    level = 0;
    xp = 0;
    max_hp = 0;
    hp = 0;

    // Initialize attributes.
    strength = 0;
    fortitude = 0;

    // Initialize possessions.
    items = new Inventory;
    weapon = nullptr;
    armor = nullptr;
}

Actor::~Actor()
{
    // Delete possessions.
    delete items;

    if (weapon != nullptr)
    {
        delete weapon;
    }

    if (armor != nullptr)
    {
        delete armor;
    }
}

void Actor::attack(Actor& target)
{
    // Calculate damage.
    int atk = calc_atk();
    int damage = roll(1, atk);

    int net_damage = target.hurt(damage);

    // Report attack results.
    std::cout << "The " << name;
    std::cout << " deals " << net_damage;
    std::cout << " damage to ";

    // Report who the target was.
    if (&target == &player)
    {
        // If the target was the player.
        std::cout << "you.\n";
        std::cout << "Your current health is " << target.get_hp();
        std::cout << ".\n\n";
    }
    else
    {
        std::string target_name = target.get_name();
        std::cout << "the " << target_name << ".\n";
        std::cout << "The " << target_name << "'s current health is ";
        std::cout << target.get_hp() << ".\n\n";
    }
}

int Actor::hurt(int damage)
{
    // Sanity check. Damage cannot be negative.
    assert(damage >= 0);

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

int Actor::heal(int points)
{
    // Sanity check. Healing cannot be negative.
    assert(points >= 0);

    int hp_before = hp;

    hp += points;

    // Respect hp limits.
    if (hp > max_hp)
    {
        hp = max_hp;
    }

    // Return net healing.
    return hp - hp_before;
}

void Actor::level_up()
{
    xp = 0;
    level++;
}

int Actor::calc_atk()
{
    int atk = strength;

    // Check if this Actor is wielding a weapon.
    if (weapon != nullptr)
    {
        atk += weapon->get_atk();
    }

    return atk;
}

int Actor::calc_def()
{
    int def = fortitude;

    // Check if this Actor is wearing armor.
    if (armor != nullptr)
    {
        def += armor->get_def();
    }

    return def;
}

std::string Actor::get_name() const
{
    return name;
}

void Actor::set_name(const std::string& s)
{
    name = s;
}

int Actor::get_hp() const
{
    return hp;
}

void Actor::set_hp(int val)
{
    hp = val;
}

int Actor::get_level() const
{
    return level;
}

void Actor::set_level(int val)
{
    level = val;
}
