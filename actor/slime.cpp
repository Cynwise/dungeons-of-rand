/**
 * @file slime.cpp
 */

#include <actor/slime.h>
#include <rng.h>

Slime::Slime()
{
    std::string slime_color[4] = {"green slime","blue slime","red slime","black slime"};
    int x = rng(0,3);

    name = slime_color[x];
    level = 1;
    max_hp = 5;
    hp = max_hp;
}

Slime* Slime::clone()
{
    Slime* tmp = new Slime;
    *tmp = *this;
    return tmp;
}
