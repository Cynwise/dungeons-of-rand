/**
 * @file inventory.h
 * @brief Container for multiple instances of different Items
 * in a single collection, and providing methods for accessing and
 * manipulating the stored Items.
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <list>
#include <string>
#include <utility>

class Item;

/**
 * @brief Generic storage supporting multiple instances of different
 * classes derived from Item.
 */
class Inventory
{
public:

    /// Initialize an empty inventory.
    Inventory();

    /// Delete all contents.
    ~Inventory();

    /// Insert an item into the inventory.
    void insert(Item& item);

    /// Finds an item by name.
    Item* find_by_name(const std::string& key) const;

private:

    /// Generic container for different kinds of items.
    std::list<Item*> contents;
};

#endif // INVENTORY_H
