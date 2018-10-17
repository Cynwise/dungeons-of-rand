/**
 * @file weapon.cpp
 */

#include <item/weapon.h>

Weapon::Weapon()
{
    atk = 0;
}

int Weapon::get_atk()
{
    return atk;
}
