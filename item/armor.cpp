/**
 * @file armor.cpp
 */

#include <iostream>
#include <string>

#include <armor_module.h>
#include <item/armor.h>
#include <module.h>

Armor::Armor()
{
    def = 0;
}

Armor::~Armor()
{
    // Do nothing.
}

Armor::Armor(const Armor& other)
{
    name = other.name;
    def = other.def;
}

Armor::Armor(const std::string& type)
{
	// Check if the type exists.
	auto it = armor_map.find(type);
	if (it == armor_map.end())
	{
		std::cerr << "ARMOR DOES NOT EXIST: " << type << std::endl;
		return;
	}
	
	// Spawn an instance of "type".
	*this = armor_map[type]->create();
}

Armor* Armor::clone() const
{
    Armor* tmp = new Armor(*this);
    return tmp;
}

int Armor::get_def() const
{
    return def;
}
