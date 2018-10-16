/**
 * @file snake.cpp
 */

#include <actor/snake.h>
#include <rng.h>

Snake::Snake()
{
    name = "snake";
    level = rng(1, 3);
    max_hp = 10 + level;
    hp = max_hp;
}

Snake* Snake::clone()
{
    Snake* tmp = new Snake;
    *tmp = *this;
    return tmp;
}
