/**
 * @file shaman.cc implementation for shaman.h file
 */

#include <actor/shaman.h>
#include <rng.h>

Shaman::Shaman()
{
    name = "shaman";
    level = 1;
    max_hp = 10;
    hp = max_hp;
}

Dragon* Shaman::Shaman()
{
    Shaman* tmp = new Shaman;
    *tmp = *this;
    return tmp;
}
