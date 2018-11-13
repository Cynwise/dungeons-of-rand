/**
 * @file weapon.cpp
 */

#include <iostream>
#include <string>

#include <actor.h>
#include <item/weapon.h>
#include <module.h>
#include <weapon_module.h>

Weapon::Weapon()
{
    atk = 0;
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
}

Weapon::Weapon(const std::string& weapon_type)
{
    // Check if the type exists.
    auto it = weapon_map.find(weapon_type);
    if (it == weapon_map.end())
    {
        std::cerr << "WEAPON DOES NOT EXIST: " << weapon_type << std::endl;
        return;
    }

    // Spawn an instance of "type".
    Weapon_Module& parent = *weapon_map[weapon_type];
    type = weapon_type;
    name = parent.name;
    atk = parent.atk;
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
        holder.add_item(*prev_equipped);
    }

    holder.weapon.reset(clone());
    std::cout << "You wield the " << name << ".\n";

    // Remove self from Actor inventory.
    holder.remove_item(*this);

    return true;
}
void Weapon::check(Actor& holder)
{
    std::cout << name << " gives you " << atk << " attack.\n";
}

int Weapon::get_atk() const
{
    return atk;
}
