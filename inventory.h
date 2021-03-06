/**
 * @file inventory.h
 * @brief Container for multiple instances of different Items
 * in a single collection, and providing methods for accessing and
 * manipulating the stored Items.
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <list>
#include <memory>
#include <string>
#include <utility>

class Item;
class Room;

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

    /// Assignment operator.
    Inventory& operator=(const Inventory& other);

    /// Insert an item into the inventory.
    void insert(std::unique_ptr<Item> item);

    /// Remove an item from the inventory.
    std::unique_ptr<Item> remove(Item* item);

    /// Dump all items in the inventory into a room.
    void dump_items(Room& room);

    /// Finds an item by name.
    Item* find_by_name(const std::string& key) const;

    /// Lists the contents of the inventory.
    void print() const;

private:

    /// Generic container for different kinds of items.
    std::list<std::unique_ptr<Item>> contents;
};

#endif // INVENTORY_H
