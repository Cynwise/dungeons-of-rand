/**
 * @file inventory.cpp
 * @brief Inventory class operations.
 */

#include <iostream>
#include <list>
#include <memory>

#include <inventory.h>
#include <item.h>
#include <room.h>

Inventory::Inventory()
{
    // Do nothing.
}

Inventory::~Inventory()
{
    // Stored items will be free'd when their unique_ptr's leave scope.
}

Inventory& Inventory::operator=(const Inventory& other)
{
    // Delete the existing contents if they exist.
    contents.clear();

    // Copy the other inventory.
    for (auto it = other.contents.begin(); it != other.contents.end(); ++it)
    {
        insert(**it);
    }

    return *this;
}

void Inventory::insert(const Item& item)
{
    // We use C++11 move semantics to move the cloned item into the list.
    std::unique_ptr<Item> new_item(item.clone());
    contents.push_back(std::move(new_item));
}

std::unique_ptr<Item> Inventory::remove(Item& item)
{
    std::unique_ptr<Item> removed = nullptr;

    // Iterate over list until we find the target actor.
    for (auto it = contents.begin(); it != contents.end(); ++it)
    {
        // Check if we found the target.
        if (&item == (*it).get())
        {
            removed = std::move(*it);
            contents.erase(it);
            break;
        }
    }

    return removed;
}

void Inventory::dump_items(Room& room)
{
    for (auto it = contents.begin(); it != contents.end(); ++it)
    {
        player_room->add_item(**it);
        remove(**it);
        it = contents.begin();
    }
}

void Inventory::print() const
{
    // Note that we are printing from 1, whereas real indices start
    // from 0.
    size_t index = 1;

    // Iterate over list until we've found all items.
    for (auto it = contents.begin(); it != contents.end(); ++it)
    {
        std::cout << index << ". " << (*it)->get_name() << std::endl;
        ++index;
    }
}

Item* Inventory::find_by_name(const std::string& key) const
{
    // Iterate over list until we find the target actor.
    for (auto it = contents.begin(); it != contents.end(); ++it)
    {
        // Check if we found the target.
        if (key == (*it)->get_name())
        {
            return it->get();
        }
    }

    // Else.
    return nullptr;
}
