/**
 * @file armor.cpp
 */

#include <iostream>
#include <string>

#include <actor.h>
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

bool Armor::equip(Actor& holder)
{
    // Check if the actor already is wearing armor.
    if (holder.armor.get() != nullptr)
    {
        // Add the armor back to the actor's inventory.
        auto prev_equipped = std::move(holder.armor);
        std::cout << "You place the " << prev_equipped->get_name();
        std::cout << " back into your inventory.\n";
        holder.add_item(std::move(prev_equipped));
    }

    holder.armor.reset(clone());
    std::cout << "You equip the " << name << ".\n";

    // Remove self from Actor's inventory.
    holder.remove_item(*this);

    return true;
}
void Armor::check(Actor& holder)
{
    std::cout << "This is a " << name << ".\n";
    std::cout << "It gives you " << def << " defense.\n";
}

int Armor::get_def() const
{
    return def;
}
