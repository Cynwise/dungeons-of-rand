/**
 * @file weapon.cpp
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include <actor.h>
#include <item/weapon.h>
#include <module.h>
#include <weapon_module.h>

Weapon::Weapon()
{
    atk = 0;
    to_hit = 0;
}

Weapon::~Weapon()
{
    // Do nothing.
}

Weapon::Weapon(const Weapon& other)
{
    type = other.type;
    name = other.name;
    atk = other.atk;
    to_hit = other.to_hit;
    attack_list = other.attack_list;
}

Weapon::Weapon(const std::string& weapon_type)
{
    // Check if the type exists.
    auto it = weapon_map.find(weapon_type);
    if (it == weapon_map.end())
    {
        std::cerr << "WEAPON DOES NOT EXIST: " << weapon_type << std::endl;
        std::exit(1);
    }

    // Spawn an instance of "type".
    Weapon_Module& parent = *weapon_map[weapon_type];
    type = weapon_type;
    name = parent.name;
    atk = parent.atk;
    to_hit = parent.to_hit;
    attack_list = parent.attack_list;
}

Weapon* Weapon::clone() const
{
    Weapon* tmp = new Weapon(*this);
    return tmp;
}

bool Weapon::equip(Actor& holder)
{
    // Check if the actor already is wielding a weapon.
    if (holder.weapon.get() != nullptr)
    {
        // Add the weapon back to the actor's inventory.
        auto prev_equipped = std::move(holder.weapon);
        std::cout << "You place the " << prev_equipped->get_name();
        std::cout << " back into your inventory.\n";
        holder.add_item(std::move(prev_equipped));
    }

    holder.weapon.reset(clone());
    std::cout << "You wield the " << name << ".\n\n";

    // Remove self from Actor inventory.
    holder.remove_item(this);

    return true;
}
void Weapon::check(Actor& holder)
{
    std::cout << "This is a " << name << ".\n";
    std::cout << "It gives you " << atk << " attack";

    // Report hit chance modifier.
    if (to_hit == 0)
    {
        std::cout << ".\n\n";
    }
    else if (to_hit > 0)
    {
        std::cout << " and a +" << to_hit << " modifier to hit chance.\n\n";
    }
    else
    {
        std::cout << " and a " << to_hit << " modifier to hit chance.\n\n";
    }
}

int Weapon::get_atk() const
{
    return atk;
}

int Weapon::get_to_hit() const
{
    return to_hit;
}
