/**
 * @file barbarian.cpp
 */

#include <actor/barbarian.h>
#include <rng.h>

Barbarian::Barbarian()
{
    name = "barbarian";
    level = 1;
    max_hp = 10;
    hp = max_hp;
}

Barbarian* Barbarian::clone()
{
    Barbarian* tmp = new Barbarian;
    *tmp = *this;
    return tmp;
}
