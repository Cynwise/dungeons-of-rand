/**
 * @file armor.h
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

private:

    /// Defense boost granted by this armor.
    int def;
};

#endif // ARMOR_H
