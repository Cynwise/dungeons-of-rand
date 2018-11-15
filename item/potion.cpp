/**
 * @file potion.cpp
 */

#include <iostream>
#include <string>

#include <actor.h>
#include <potion_module.h>
#include <item/potion.h>
#include <module.h>

Potion::Potion()
{
    stat = 0;
}

Potion::~Potion()
{
    // Do nothing.
}

Potion::Potion(const Potion& other)
{
    name = other.name;
    stat = other.stat;
}

Potion::Potion(const std::string& potion_type)
{
    // Check if the type exists.
    auto it = potion_map.find(potion_type);
    if (it == potion_map.end())
    {
        std::cerr << "POTION DOES NOT EXIST: " << potion_type << std::endl;
        std::exit(1);
    }

    // Spawn an instance of "type".
    Potion_Module& parent = *potion_map[potion_type];
    type = potion_type;
    name = parent.name;
    stat = parent.stat;
}

Potion* Potion::clone() const
{
    return new Potion(*this);
}

void Potion::use(Actor& holder)
{
    // Apply health change.
    int delta = holder.heal(stat);

    std::cout << "You use the " << name << " and regain ";
    std::cout << delta << " health.\n";
    std::cout << "Your current health is ";
    std::cout << holder.hp << "/";
    std::cout << holder.max_hp << ".\n\n";

    // Remove self from Actor's inventory.
    holder.remove_item(this);
}

void Potion::check(Actor& holder)
{
    std::cout << "This is a " << name << ".\n";
    std::cout << "It gives you " << stat << " health.\n\n";
}

int Potion::get_stat() const
{
    return stat;
}
