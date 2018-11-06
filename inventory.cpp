/**
 * @file inventory.cpp
 * @brief Inventory class operations.
 */

#include <list>

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
