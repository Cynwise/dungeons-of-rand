/**
 * @file potion.h
 * @brief Generic potion base class.
 */

#ifndef POTION_H
#define POTION_H

#include <string>

#include <item.h>

/// Generic potion class.
class Potion : public Item
{
public:

    Potion();

    virtual ~Potion();

    Potion(const Potion& other);

    Potion(const std::string& type);

    virtual Potion* clone() const;

    /// Make the actor .
    virtual void use(Actor& holder);

    /// Gets the stats on potion.
    int get_stat() const;

private:

    /// Defense boost granted by this armor.
    int stat;
};

#endif // POTION_H
