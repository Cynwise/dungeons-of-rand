/**
 * @file weapon.h
 * @brief Generic weapon base class.
 */

#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include <item.h>

/// Generic equipable weapon class.
class Weapon : public Item
{
public:

    Weapon();

    virtual ~Weapon();

    Weapon(const std::string& type);

    Weapon(const Weapon& other);

    virtual Weapon* clone() const;

    /// Make the actor wield this weapon.
    virtual bool equip(Actor& holder);

    /// Gets this weapon's attack value.
    int get_atk() const;

private:

    /// Attack boost granted by this weapon.
    int atk;
};

#endif // WEAPON_H
