/**
 * @file centaur.cpp
 */

#include <actor/centaur.h>
#include <rng.h>

Centaur::Centaur()
{
    name = "centaur";
    level = 1;
    max_hp = 20;
    hp = max_hp;

    strength = 6;
    fortitude = 4;
}

Centaur* Centaur::clone()
{
    Centaur* tmp = new Centaur;
    *tmp = *this;
    return tmp;
}
