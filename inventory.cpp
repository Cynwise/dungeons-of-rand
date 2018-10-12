/**
 * @file inventory.cpp
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
    std::list<Item*>::iterator it;

    // Iterate over list and delete all contents.
    for (it = contents.begin(); it != contents.end(); ++it)
    {
        delete *it;
    }
}

void Inventory::insert(Item& item)
{
    Item* tmp = item.clone();
    contents.push_back(tmp);
}
