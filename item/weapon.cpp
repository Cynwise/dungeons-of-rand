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

int Weapon::get_atk() const
{
    return atk;
}
