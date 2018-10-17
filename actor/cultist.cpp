/**
 * @file cultist.cpp
 */

#include <actor/cultist.h>
#include <rng.h>

Cultist::Cultist()
{
    name = "cultist";
    level = 1;
    max_hp = 10;
    hp = max_hp;

    strength = 7;
    fortitude = 3;
}

Cultist* Cultist::clone()
{
    Cultist* tmp = new Cultist;
    *tmp = *this;
    return tmp;
}
