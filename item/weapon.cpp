/**
 * @file weapon.cpp
 */

#include <item/weapon.h>

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

Weapon* Weapon::clone() const
{
    Weapon* tmp = new Weapon(*this);
    return tmp;
}

int Weapon::get_atk() const
{
    return atk;
}
