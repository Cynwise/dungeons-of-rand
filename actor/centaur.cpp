/**
 * @file centaur.cpp
 */

#include <actor/centaur.h>
#include <rng.h>

Centaur::Centaur()
{
    name = "centaur";
    level = 1;
    max_hp = 10;
    hp = max_hp;
}

Centaur* Centaur::clone()
{
    Centaur* tmp = new Centaur;
    *tmp = *this;
    return tmp;
}
