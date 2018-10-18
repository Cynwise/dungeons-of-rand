/**
 * @file item.h
 * @brief Generic item base class.
 */

#ifndef ITEM_H
#define ITEM_H

#include <string>

class Actor;

/// Generic base class for usable items.
class Item
{
public:

    Item();

    virtual ~Item() = 0;

    /// Returns a dynamically allocated copy of this object.
    virtual Item* clone() const = 0;

    /// Apply the item's effects to actor.
    virtual void use(Actor& user) = 0;

protected:

    std::string name;
};

#endif // ITEM_H
