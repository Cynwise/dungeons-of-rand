/**
 * @file goblin.cpp
 */

#include <actor/goblin.h>
#include <rng.h>

Goblin::Goblin()
{
    name = "goblin";
    level = 1;
    max_hp = 10;
    hp = max_hp;

    strength = 3;
    fortitude = 2;
}

Goblin* Goblin::clone()
{
    Goblin* tmp = new Goblin;
    *tmp = *this;
    return tmp;
}
