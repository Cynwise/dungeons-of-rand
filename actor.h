/**
 * @file actor.h
 * @brief Base class for all creatures, including the player and any
 * NPCs.
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <memory>
#include <string>

#include <inventory.h>

class Armor;
class Item;
class Weapon;

/// Generic base class for all NPCs.
class Actor
{
public:

    /// Should not be used.
    Actor();

    /// Copy constructor.
    Actor(const Actor& other);

    /// Create an actor of the given type.
    Actor(std::string type);

    virtual ~Actor();

    /// Assignment operator.
    Actor& operator=(const Actor& other);

    /// Make attack against another actor.
    virtual void attack(Actor& target);

    /**
     * @brief Receive damage.
     *
     * @param damage Base damage applied. Net damage may be different
     * depending on the actor's stats, equipment, etc.
     *
     * @return The net amount of damage applied to this actor.
     */
    virtual int hurt(int damage);

    /**
     * @brief Increase HP.
     *
     * @param points Base healing applied. Net damage may be different
     * depending on the actor's stats, max health, etc.
     *
     * @return The net amount of healing applied to this actor.
     */
    virtual int heal(int points);

    /// Levels up actor and zeros XP.
    void level_up();

    /// Calculates the actor's attack value.
    int calc_atk() const;

    /// Calculates the actor's defensive value.
    int calc_def() const;

    // Getters and setters.
    std::string get_name() const;
    void set_name(const std::string& s);
    int get_hp() const;
    void set_hp(int val);
    int get_level() const;
    void set_level(int val);

protected:

    /// Identifier for this Actor type.
    std::string type;

    std::string name;
    int level;
    int xp;
    int max_hp;
    int hp;

    // Attributes.
    int strength;
    int fortitude;

    // Possessions.
    Inventory items;
    std::unique_ptr<Weapon> weapon;
    std::unique_ptr<Armor> armor;
};

#endif // ACTOR_H
