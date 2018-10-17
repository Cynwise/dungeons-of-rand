/**
 * @file armor.h
 * @brief Generic armor base class.
 */

#ifndef ARMOR_H
#define ARMOR_H

#include <item.h>

/// Generic equipable armor class.
class Armor : Item
{
public:

    Armor();

    virtual ~Armor() = 0;

    virtual Armor* clone() = 0;

    /// Gets the defensive value of this armor.
    int get_def();

private:

    /// Defense boost granted by this armor.
    int def;
};

#endif // ARMOR_H
