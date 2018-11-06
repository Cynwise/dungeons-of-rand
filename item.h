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

    Item(const std::string& type);

    /// Returns a dynamically allocated copy of this object.
    virtual Item* clone() const;

    /// Apply the item's effects to actor.
    virtual void use(Actor& user);

protected:

    friend class Item_Module;

    std::string type;

    std::string name;
};

/// Helper function that spawns an item type which can be a derived
/// type.
std::unique_ptr<Item> spawn_item(const std::string& type);

#endif // ITEM_H
