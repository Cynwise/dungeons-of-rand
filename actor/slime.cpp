/**
 * @file slime.cpp
 */

#include <actor/slime.h>
#include <rng.h>

Slime::Slime()
{
    std::string slime_color[4] =
    {
        "green",
        "blue",
        "red",
        "black"
    };
    int x = rng(0,3);

    name = slime_color[x] + " slime";
    level = 1;
    max_hp = 10;
    hp = max_hp;

    strength = 2;
    fortitude = 8;
}

Slime* Slime::clone()
{
    Slime* tmp = new Slime;
    *tmp = *this;
    return tmp;
}
