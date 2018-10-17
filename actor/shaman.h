/**
 * @file shaman.h
 * @brief magical enemy class.
 */

#ifndef SHAMAN_H
#define SHAMAN_H

#include <actor.h>

/// Simple enemy class.
class Shaman : public Actor
{
public:

    Shaman();

    Shaman* clone();
};

#endif // SHAMAN_H
