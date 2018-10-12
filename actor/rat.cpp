/**
 * @file rat.cpp
 */

#include <actor/rat.h>
#include <rng.h>

Rat::Rat()
{
    name = "rat";
    level = 5;
    max_hp = 20;
    hp = max_hp;
}

Rat* Rat::clone()
{
    Rat* tmp = new Rat;
    *tmp = *this;
    return tmp;
}

void Rat::attack(Actor& target)
{
    int damage = roll(1, level + 1, 0);

    target.hurt(damage);
}
