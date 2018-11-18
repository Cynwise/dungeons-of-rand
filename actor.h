/**
 * @file actor.h
 * @brief Base class for all creatures, including the player and any
 * NPCs.
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <memory>
#include <string>
#include <vector>

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

    /// Make random attack against another actor.
    virtual void attack(Actor& target);

    /// Make specific attack against another actor.
    virtual void attack(
        Actor& target,
        const std::string& attack_name,
        const std::string& verb);

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

    /// Determine whether an attack hits or misses.
    bool is_hit(const Actor& target) const;

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
    virtual std::unique_ptr<Item> remove_item(Item* item);

    virtual Item* find_item(const std::string& name);

    /// Dumps all items into a room.
    virtual void dump_items(Room& room);

    /// Display the contents of the Actor's inventory.
    virtual void print_inventory();

    /// Level up actor and zero XP.
    void level_up();

    /// Calculate the actor's attack value.
    int calc_atk() const;

    /// Calculate the actor's defensive value.
    int calc_def() const;

    /// Returns whether the actor is wielding a weapon.
    bool has_weapon() const;

    // Getters and setters.
    std::string get_name() const;
    void set_name(const std::string& s);
    int get_hp() const;
    void set_hp(int val);
    int get_level() const;
    void set_level(int val);
    int get_strength() const;
    void set_strength(int val);
    int get_fortitude() const;
    void set_fortitude(int val);
    int get_agility() const;
    void set_agility(int val);
    int get_dexterity() const;
    void set_dexterity(int val);
    int get_gold() const;
    void set_gold(int val);
    const std::string& get_combat_start() const;
    const std::string& get_win_msg() const;
    const std::string& get_lose_msg() const;

    /// Whether the player has fought this exact Actor before.
    bool encountered;

    // Possible attack types.
    std::vector<std::string> attack_list;

    // Possessions.
    std::unique_ptr<Weapon> weapon;
    std::unique_ptr<Armor> armor;

protected:

    // Allow items and attack types protected access to the Actor.
    friend class Attack_Type;
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
    int gold;

    // Attributes.
    int strength;
    int fortitude;
    int agility;
    int dexterity;

    // Possessions.
    Inventory items;

    // Combat messages.
    std::vector<std::string> combat_start;
    std::vector<std::string> win_msg;
    std::vector<std::string> lose_msg;
};

/// Spawns an actor of a given type.
std::unique_ptr<Actor> spawn_actor(const std::string& actor_type);

#endif // ACTOR_H
