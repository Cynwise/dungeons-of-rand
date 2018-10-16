/**
 * @file bear.h
 * @brief Simple animal enemy class.
 */

#ifndef BEAR_H
#define BEAR_H

#include <actor.h>

/// Simple enemy class.
class Bear : public Actor
{
public:

   Bear();

    Bear* clone();
};

#endif // BEAR_H
