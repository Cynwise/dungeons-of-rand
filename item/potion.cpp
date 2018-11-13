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
        return;
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
    holder.heal(stat);

    holder.potion.reset(clone());
    std::cout << "You use the " << name << ".\n";

    // Remove self from Actor's inventory.
    holder.remove_item(this);

}
void Potion::check(Actor& holder)
{
    std::cout << "This is a " << name << ".\n";
    std::cout << "It gives you " << stat << " health.\n";
}

int Potion::get_stat() const
{
    return stat;
}
