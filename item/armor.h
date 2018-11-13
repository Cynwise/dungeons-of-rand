/**
 * @file armor.h
 * @brief Generic armor base class.
 */

#ifndef ARMOR_H
#define ARMOR_H

#include <string>

#include <item.h>

/// Generic equipable armor class.
class Armor : public Item
{
public:

    Armor();

    virtual ~Armor();

    Armor(const Armor& other);

    Armor(const std::string& type);

    virtual Armor* clone() const;

    /// Make the actor wield this armor.
    virtual bool equip(Actor& holder);

    /// Gets the defensive value of this armor.
    int get_def() const;

    /// Shows player armor stats.
    virtual void check(Actor& holder);

private:

    /// Defense boost granted by this armor.
    int def;
};

#endif // ARMOR_H
