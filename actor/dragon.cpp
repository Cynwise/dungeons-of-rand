/**
 * @file dragon.cpp
 */

#include <actor/dragon.h>
#include <rng.h>

Dragon::Dragon()
{
    name = "dragon";
    level = 1;
    max_hp = 10;
    hp = max_hp;
}

Dragon* Dragon::clone()
{
    Dragon* tmp = new Dragon;
    *tmp = *this;
    return tmp;
}
