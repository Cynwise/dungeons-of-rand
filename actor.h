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
class Room;
class Weapon;
class Potion;

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

    /**
     * @brief Add an item to the Actor's inventory.
     *
     * @param item Item to be added.
     */
    virtual void add_item(std::unique_ptr<Item> item);

    /**
     * @brief Remove an item from the Actor's inventory.
     *
     * @param pos Position in the list to remove from.
     *
     * @return Pointer to the item that was removed, or nullptr if
     * no item was removed.
     */
    virtual std::unique_ptr<Item> remove_item(Item& item);

    virtual Item* find_item(const std::string& name);

    /// Dumps all items into a room.
    virtual void dump_items(Room& room);

    /// Display the contents of the Actor's inventory.
    virtual void print_inventory();

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

    // Allow items to modify the Actor.
    friend class Item;
    friend class Weapon;
    friend class Armor;
    friend class Potion;

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
    std::unique_ptr<Potion> potion;
};

#endif // ACTOR_H
