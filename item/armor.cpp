/**
 * @file armor.cpp
 */

#include <item/armor.h>

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

Armor* Armor::clone() const
{
    Armor* tmp = new Armor(*this);
    return tmp;
}

int Armor::get_def() const
{
    return def;
}
