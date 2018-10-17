/**
 * @file dragon.cpp
 */

#include <actor/dragon.h>
#include <rng.h>

Dragon::Dragon()
{
    name = "dragon";
    level = 1;
    max_hp = 50;
    hp = max_hp;

    strength = 10;
    fortitude = 10;
}

Dragon* Dragon::clone()
{
    Dragon* tmp = new Dragon;
    *tmp = *this;
    return tmp;
}
