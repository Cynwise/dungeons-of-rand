/**
 * @file cultist.h
 * @brief Simple humanoid enemy class.
 */

#ifndef CULTIST_H
#define CULTIST_H

#include <actor.h>

/// Simple enemy class.
class Cultist : public Actor
{
public:

    Cultist();

    Cultist* clone();
};

#endif // CULTIST_H
