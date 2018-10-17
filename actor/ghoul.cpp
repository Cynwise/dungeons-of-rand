/**
 * @file ghoul.cpp
 */

#include <actor/ghoul.h>
#include <rng.h>

Ghoul::Ghoul()
{
    name = "ghoul";
    level = 1;
    max_hp = 10;
    hp = max_hp;

    strength = 12;
    fortitude = 10;
}

Ghoul* Ghoul::clone()
{
    Ghoul* tmp = new Ghoul;
    *tmp = *this;
    return tmp;
}
