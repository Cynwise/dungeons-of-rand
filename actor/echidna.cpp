/**
 * @file echidna.cpp
 */

#include <actor/echidna.h>
#include <rng.h>

Echidna::Echidna()
{
    name = "echidna";
    level = 1;
    max_hp = 10;
    hp = max_hp;

    strength = 1;
    fortitude = 1;
}

Echidna* Echidna::clone()
{
    Echidna* tmp = new Echidna;
    *tmp = *this;
    return tmp;
}
