/**
 * @file weapon.h
 * @brief Generic weapon base class.
 */

#ifndef WEAPON_H
#define WEAPON_H

#include <item.h>

/// Generic equipable weapon class.
class Weapon : Item
{
public:

    Weapon();

    virtual ~Weapon() = 0;

    virtual Weapon* clone() = 0;

    /// Gets this weapon's attack value.
    int get_atk();

private:

    /// Attack boost granted by this weapon.
    int atk;
};

#endif // WEAPON_H
