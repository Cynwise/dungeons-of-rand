/**
 * @file giant.h
 * @brief Humaniod giant class
 */

#ifndef GIANT_H
#define GIANT_H

#include <actor.h>

/// Simple enemy class.
class Giant : public Actor
{
public:

    Giant();

    Giant* clone();
};

#endif // GIANT_H
