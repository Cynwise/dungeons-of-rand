/**
 * @file snake.h
 * @brief Simple animal enemy class.
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <actor.h>

/// Simple enemy class.
class Snake : public Actor
{
public:

    Snake();

    Snake* clone();
};

#endif // SNAKE_H
