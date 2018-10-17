/**
 * @file cultist.h
 * @brief Simple dragon enemy class.
 */

#ifndef DRAGON_H
#define DRAGON_H

#include <actor.h>

/// Simple enemy class.
class Dragon : public Actor
{
public:

    Dragon();

    Dragon* clone();
};

#endif // DRAGON_H
