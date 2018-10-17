/**
 * @file bear.cpp
 */

#include <actor/bear.h>
#include <rng.h>

Bear::Bear()
{
    name = "bear";
    level = 1;
    max_hp = 20;
    hp = max_hp;

    strength = 8;
    fortitude = 5;
}

Bear* Bear::clone()
{
    Bear* tmp = new Bear;
    *tmp = *this;
    return tmp;
}
