/**
 * @file weapon.h
 * @brief Generic weapon base class.
 */

#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <vector>

#include <item.h>

class Attack_Type;

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

    virtual void check(Actor& holder);

    /// Gets this weapon's attack value.
    int get_atk() const;

    /// List of attacks that can be performed with this weapon.
    std::vector<Attack_Type*> attack_list;

private:

    /// Attack boost granted by this weapon.
    int atk;
};

#endif // WEAPON_H
