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

    /// Lets the actor use item .
    virtual void use(Actor& holder);

    /// Lets actor check item.
    virtual void check(Actor& holder);

    /// Gets the stats on potion.
    int get_stat() const;

private:

    /// Defense boost granted by this armor.
    int stat;
};

#endif // POTION_H
