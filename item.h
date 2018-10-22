/**
 * @file item.h
 * @brief Generic item base class.
 */

#ifndef ITEM_H
#define ITEM_H

#include <memory>
#include <string>

class Actor;

/// Generic base class for usable items.
class Item
{
public:

    Item();

    virtual ~Item();

    /// Returns a dynamically allocated copy of this object.
    virtual Item* clone() const;

    /// Apply the item's effects to actor.
    virtual void use(Actor& user);

protected:

    std::string name;
};

#endif // ITEM_H
