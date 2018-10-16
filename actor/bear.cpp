/**
 * @file bear.cpp
 */

#include <actor/bear.h>
#include <rng.h>

Bear::Bear()
{
    name = "bear";
    level = 1;
    max_hp = 10;
    hp = max_hp;
}

Bear* Bear::clone()
{
    Bear* tmp = new Bear;
    *tmp = *this;
    return tmp;
}
