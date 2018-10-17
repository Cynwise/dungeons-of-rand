/**
 * @file giant.cpp
 */

#include <actor/giant.h>
#include <rng.h>

Giant::Giant()
{
    name = "giant";
    level = 1;
    max_hp = 20;
    hp = max_hp;

    strength = 15;
    fortitude = 10;
}

Giant* Giant::clone()
{
    Giant* tmp = new Giant;
    *tmp = *this;
    return tmp;
}
