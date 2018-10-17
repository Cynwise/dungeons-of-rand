/**
 * @file ghoul.h
 * @brief an undead humanoid monstrosity
 */

#ifndef GHOUL_H
#define GHOUL_H

#include <actor.h>

/// Simple enemy class.
class Ghoul : public Actor
{
public:

    Ghoul();

    Ghoul* clone();
};

#endif // GHOUL_H
