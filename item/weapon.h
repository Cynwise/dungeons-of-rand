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

    /// Gets this weapon's attack value.
    int get_atk() const;

private:

    friend class Weapon_Module;

    /// Attack boost granted by this weapon.
    int atk;
};

#endif // WEAPON_H
