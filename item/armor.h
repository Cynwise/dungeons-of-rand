/**
 * @file armor.h
 * @brief Generic armor base class.
 */

#ifndef ARMOR_H
#define ARMOR_H

#include <item.h>

/// Generic equipable armor class.
class Armor : public Item
{
public:

    Armor();

    virtual ~Armor();

    Armor(const Armor& other);

    virtual Armor* clone() const;

    /// Gets the defensive value of this armor.
    int get_def() const;

private:

    /// Defense boost granted by this armor.
    int def;
};

#endif // ARMOR_H
