/**
 * @file item.cpp
 * @brief Generic item base class implementation.
 */

#include <iostream>
#include <memory>
#include <string>

#include <actor.h>
#include <item.h>
#include <item_module.h>
#include <item/armor.h>
#include <item/potion.h>
#include <item/weapon.h>
#include <module.h>
#include <room.h>

std::unique_ptr<Item> spawn_item(const std::string& type)
{
    // First, check for generic items.
    auto item_it = item_map.find(type);
    if (item_it != item_map.end())
    {
        return std::unique_ptr<Item>(new Item(type));
    }

    // Next, check for weapon types.
    auto weapon_it = weapon_map.find(type);
    if (weapon_it != weapon_map.end())
    {
        return std::unique_ptr<Item>(new Weapon(type));
    }

    // Next, check for armor types.
    auto armor_it = armor_map.find(type);
    if (armor_it != armor_map.end())
    {
        return std::unique_ptr<Item>(new Armor(type));
    }

    // Next, check for potion types.
    auto potion_it = potion_map.find(type);
    if (potion_it != potion_map.end())
    {
        return std::unique_ptr<Item>(new Potion(type));
    }

    // Else.
    std::cerr << "ITEM DOES NOT EXIST: " << type << std::endl;
    return nullptr;
}

Item::Item()
{
    name = "[GENERIC ITEM]";
}

Item::~Item()
{
    // Do nothing.
}

Item::Item(const std::string& item_type)
{
    // Check if the type exists.
    auto it = item_map.find(item_type);
    if (it == item_map.end())
    {
        std::cerr << "ITEM DOES NOT EXIST: " << item_type << std::endl;
        return;
    }

    // Spawn an instance of "type".
    Item_Module& parent = *item_map[item_type];
    type = parent.type;
    name = parent.name;
}

Item* Item::clone() const
{
    return new Item(*this);
}

void Item::use(Actor& user)
{
    std::cout << "You can't use that.\n";
}

bool Item::equip(Actor& holder)
{
    std::cout << "That item cannot be equipped.\n";
    return false;
}

const std::string& Item::get_type() const
{
    return type;
}

const std::string& Item::get_name() const
{
    return name;
}

void Item::set_name(const std::string& s)
{
    name = s;
}
