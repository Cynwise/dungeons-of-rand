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

Armor::Armor(const std::string& armor_type)
{
    // Check if the type exists.
    auto it = armor_map.find(armor_type);
    if (it == armor_map.end())
    {
        std::cerr << "ARMOR DOES NOT EXIST: " << armor_type << std::endl;
        return;
    }

    // Spawn an instance of "type".
    Armor_Module& parent = *armor_map[armor_type];
    type = armor_type;
    name = parent.name;
    def = parent.def;
}

Armor* Armor::clone() const
{
    return new Armor(*this);
}

int Armor::get_def() const
{
    return def;
}
