/**
 * @file inventory.cpp
 * @brief Inventory class operations.
 */

#include <iostream>
#include <list>
#include <memory>

#include <inventory.h>
#include <item.h>

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

std::unique_ptr<Item> Inventory::remove(size_t pos)
{
    // Verify that the item exists.
    if (pos >= contents.size())
    {
        return std::unique_ptr<Item>(nullptr);
    }

    // Find the element.
    auto it = contents.begin();
    std::advance(it, pos);

    // Move the element out of the list.
    auto orphan = std::move(*it);
    contents.erase(it);

    return orphan;
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
