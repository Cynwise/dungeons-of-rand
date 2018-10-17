/**
 * @file shaman.cpp
 * @brief Implementation for shaman.h.
 */

#include <actor/shaman.h>
#include <rng.h>

Shaman::Shaman()
{
    name = "shaman";
    level = 1;
    max_hp = 10;
    hp = max_hp;

    strength = 4;
    fortitude = 3;
}

Shaman* Shaman::clone()
{
    Shaman* tmp = new Shaman;
    *tmp = *this;
    return tmp;
}
