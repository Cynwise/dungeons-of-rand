/**
 * @file barbarian.h
 * @brief Simple monster enemy class.
 */

#ifndef GOBLIN_H
#define GOBLIN_H

#include <actor.h>

/// Simple enemy class.
class Goblin : public Actor
{
public:

    Goblin();

    Goblin* clone();
};

#endif // GOBLIN_H
