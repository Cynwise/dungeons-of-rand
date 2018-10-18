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
    // Iterate over list and delete all contents.
    for (auto it = contents.begin(); it != contents.end(); ++it)
    {
        delete *it;
    }
    contents.clear();
}

Inventory& Inventory::operator=(const Inventory& other)
{
    // Delete the existing contents if they exist.
    for (auto it = contents.begin(); it != contents.end(); ++it)
    {
        delete *it;
    }
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
    Item* tmp = item.clone();
    contents.push_back(tmp);
}
