/**
 * @file item.cpp
 * @brief Generic item base class implementation.
 */

#include <actor.h>
#include <item.h>
#include <room.h>

Item::Item()
{
    name = "[GENERIC ITEM]";
}

Item::~Item()
{
    // Do nothing.
}

Item* Item::clone() const
{
    Item* tmp = new Item(*this);
    return tmp;
}

void Item::use(Actor& user)
{
    // Do nothing.
}
