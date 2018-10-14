/**
 * @file rat.cpp
 */

#include <actor/rat.h>
#include <rng.h>

Rat::Rat()
{
    name = "rat";
    level = rng(1, 3);
    max_hp = 10 + level;
    hp = max_hp;
}

Rat* Rat::clone()
{
    Rat* tmp = new Rat;
    *tmp = *this;
    return tmp;
}
