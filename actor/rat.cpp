/**
 * @file rat.cpp
 */

#include <actor/rat.h>
#include <rng.h>

Rat::Rat()
{
    name = "rat";
    level = 1;
    max_hp = 10;
    hp = max_hp;
}

Rat* Rat::clone()
{
    Rat* tmp = new Rat;
    *tmp = *this;
    return tmp;
}
