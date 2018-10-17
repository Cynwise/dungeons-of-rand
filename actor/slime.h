/**
 * @file slime.h
 * @brief Simple slime enemy class.
 */

#ifndef SLIME_H
#define SLIME_H

#include <actor.h>

/// Simple enemy class.
class Slime : public Actor
{
public:

    Slime();

    Slime* clone();
};

#endif // SLIME_H
