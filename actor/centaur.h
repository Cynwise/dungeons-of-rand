/**
 * @file centaur.h
 * @brief Simple enemy class.
 */

#ifndef Centaur_H
#define Centaur_H

#include <actor.h>

/// Simple enemy class.
class Centaur : public Actor
{
public:

    Centaur();

    Centaur* clone();
};

#endif // Centaur_H
