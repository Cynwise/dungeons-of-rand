/**
 * @file rat.cpp
 */

#include <actor/rat.h>
#include <rng.h>

Rat::Rat()
{
    name = "rat";
    level = 1;
    max_hp = 5;
    hp = max_hp;

    strength = 1;
    fortitude = 1;
}

Rat* Rat::clone()
{
    Rat* tmp = new Rat;
    *tmp = *this;
    return tmp;
}
