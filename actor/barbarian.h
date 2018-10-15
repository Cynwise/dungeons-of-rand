/**
 * @file barbarian.h
 * @brief Simple humanoid enemy class.
 */

#ifndef BARBARIAN_H
#define BARBARIAN_H

#include <actor.h>

/// Simple enemy class.
class Barbarian : public Actor
{
public:

    Barbarian();

    Barbarian* clone();
};

#endif // BARBARIAN_H
