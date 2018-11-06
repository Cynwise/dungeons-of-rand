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
#include <item/weapon.h>
#include <item/armor.h>
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
	
	// Finally, check for armor types.
	auto armor_it = armor_map.find(type);
	if (armor_it != armor_map.end())
	{
		return std::unique_ptr<Item>(new Armor(type));
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

Item::Item(const std::string& type)
{
	// Check if the type exists.
	auto it = item_map.find(type);
	if (it == item_map.end())
	{
		std::cerr << "ITEM DOES NOT EXIST: " << type << std::endl;
		return;
	}
	
	// Spawn an instance of "type".
	*this = item_map[type]->create();
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
