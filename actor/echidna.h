/**
 * @file cultist.h
 * @brief Simple dragon enemy class.
 */

#ifndef ECHIDNA_H
#define ECHIDNA_H

#include <actor.h>

/// Simple enemy class.
class Echidna : public Actor
{
public:

    Echidna();

    Echidna* clone();
};

#endif // ECHIDNA_H
