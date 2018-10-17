/**
 * @file spider.cpp
 */

#include <actor/spider.h>
#include <rng.h>

Spider::Spider()
{
    name = "spider";
    level = 1;
    max_hp = 10;
    hp = max_hp;

    strength = 3;
    fortitude = 3;
}

Spider* Spider::clone()
{
    Spider* tmp = new Spider;
    *tmp = *this;
    return tmp;
}
