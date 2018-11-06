/**
 * @file weapon.cpp
 */

#include <iostream>
#include <string>

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
    name = other.name;
    atk = other.atk;
}

Weapon::Weapon(const std::string& type)
{
    // Check if the type exists.
    auto it = weapon_map.find(type);
    if (it == weapon_map.end())
    {
        std::cerr << "WEAPON DOES NOT EXIST: " << type << std::endl;
        return;
    }

    // Spawn an instance of "type".
    *this = weapon_map[type]->create();
}

Weapon* Weapon::clone() const
{
    Weapon* tmp = new Weapon(*this);
    return tmp;
}

int Weapon::get_atk() const
{
    return atk;
}
