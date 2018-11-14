/**
 * @file actor.cpp
 * @brief Generic base class behaviors for Actors.
 */

#include <cassert>
#include <iostream>
#include <string>

#include <actor.h>
#include <actor_module.h>
#include <actor/player.h>
#include <attack_type.h>
#include <item/armor.h>
#include <item/weapon.h>
#include <item/potion.h>
#include <inventory.h>
#include <module.h>
#include <rng.h>
#include <room.h>

Actor::Actor()
{
    // Initialize main stats.
    type = "[NO TYPE]";
    name = "[GENERIC ACTOR]";
    level = 0;
    xp = 0;
    max_hp = 0;
    hp = 0;

    // Initialize attributes.
    strength = 0;
    fortitude = 0;

    // Initialize possessions.
    weapon = nullptr;
    armor = nullptr;
}

Actor::Actor(const Actor& other)
{
    type = other.type;
    name = other.name;
    level = other.level;
    xp = other.xp;
    max_hp = other.max_hp;
    hp = other.hp;

    strength = other.strength;
    fortitude = other.fortitude;

    items = other.items;

    // Safely copy weapon.
    if (other.weapon != nullptr)
    {
        Weapon* new_weapon = other.weapon->clone();
        weapon.reset(new_weapon);
    }
    else
    {
        weapon = nullptr;
    }

    // Safely copy armor.
    if (other.armor != nullptr)
    {
        Armor* new_armor = other.armor->clone();
        armor.reset(new_armor);
    }
    else
    {
        armor = nullptr;
    }
}

Actor::Actor(std::string actor_type)
{
    // Initialize pointers.
    weapon = nullptr;
    armor = nullptr;

    // Check if the type exists.
    auto it = actor_map.find(actor_type);
    if (it == actor_map.end())
    {
        std::cerr << "ACTOR DOES NOT EXIST: " << actor_type << std::endl;
        return;
    }

    // Spawn an instance of this type.
    const Actor_Module& parent = *actor_map[actor_type];

    type = actor_type;
    name = parent.name;
    level = parent.level;
    max_hp = parent.max_hp;
    hp = max_hp;

    strength = parent.strength;
    fortitude = parent.fortitude;

    attack_list = parent.attack_list;

    combat_start = parent.combat_start;
    win_msg = parent.win_msg;
    lose_msg = parent.lose_msg;

    // Spawn an item from the item drop list.
    if (!parent.item_list.empty())
    {
        // Calculate the sum of Item spawn chances.
        long sum = 0;
        for (auto item_it = parent.item_list.begin(); item_it != parent.item_list.end(); ++item_it)
        {
            sum += item_it->chance;
        }

        // Generate a weighted entry value.
        long entry = rng(0, sum);

        // Iterate over the list until we find the first valid entry.
        long weighted_chance = 0;
        for (auto item_it = parent.item_list.begin(); item_it != parent.item_list.end(); ++item_it)
        {
            weighted_chance += item_it->chance;

            // Spawn the Item and add it to the Actor's inventory.
            // Don't spawn an Item with a chance of 0 or a type of "none".
            if (weighted_chance >= entry && item_it->chance != 0 && item_it->type != "none")
            {
                add_item(spawn_item(item_it->type));
                break;
            }
        }
    }
}

Actor::~Actor()
{
    // inventory will be cleaned up by its destructor.
    // weapon and armor will be cleaned up when they lose their scope.
}

Actor& Actor::operator=(const Actor& other)
{
    type = other.type;
    name = other.name;
    level = other.level;
    xp = other.xp;
    max_hp = other.max_hp;
    hp = other.hp;

    strength = other.strength;
    fortitude = other.fortitude;

    attack_list = other.attack_list;

    items = other.items;

    // Copy weapon safely.
    weapon = nullptr;
    if (other.weapon != nullptr)
    {
        weapon.reset(other.weapon->clone());
    }

    // Copy armor safely.
    armor = nullptr;
    if (other.armor != nullptr)
    {
        armor.reset(other.armor->clone());
    }

    return *this;
}

void Actor::attack(Actor& target)
{
    // Pick an attack type.
    Attack_Type* this_attack;
    if (attack_list.empty())
    {
        this_attack = attack_map["attack"];
    }
    else
    {
        int entry = rng(0, attack_list.size() - 1);
        const std::string& attack_name = attack_list[entry];
        this_attack = attack_map[attack_name];
    }

    // Calculate damage.
    int atk = calc_atk();
    int damage = roll(1, atk) + this_attack->calc_atk();

    int net_damage = target.hurt(damage);

    // Report results.
    if (net_damage > 0)
    {
        this_attack->print_attack(*this, target, net_damage);
    }
    else
    {
        std::cout << "The " << name << " attempts to attack you, ";
        std::cout << "but you dodge.\n\n";
    }
}

int Actor::hurt(int damage)
{
    // Sanity check. Damage cannot be negative.
    assert(damage >= 0);

    int hp_before = hp;

    // Calculate defense. Net def = (1d(def)-1)/2
    int def = calc_def();
    def = roll(1, def) - 1;
    def *= 0.5;

    // Apply defense to damage taken.
    damage -= def;

    // Prevent negative damage.
    if (damage < 0)
    {
        damage = 0;
    }

    // Take damage.
    hp -= damage;

    // Prevent negative health.
    if (hp < 0)
    {
        hp = 0;
    }

    // Return net damage.
    return hp_before - hp;
}

int Actor::heal(int points)
{
    // Sanity check. Healing cannot be negative.
    assert(points >= 0);

    int hp_before = hp;

    hp += points;

    // Respect hp limits.
    if (hp > max_hp)
    {
        hp = max_hp;
    }

    // Return net healing.
    return hp - hp_before;
}

void Actor::add_item(std::unique_ptr<Item> item)
{
    items.insert(std::move(item));
}

std::unique_ptr<Item> Actor::remove_item(Item* item)
{
    return items.remove(item);
}

Item* Actor::find_item(const std::string& name)
{
    return items.find_by_name(name);
}

void Actor::dump_items(Room& room)
{
    items.dump_items(room);
}

void Actor::print_inventory()
{
    items.print();
}

void Actor::level_up()
{
    xp = 0;
    level++;
}

int Actor::calc_atk() const
{
    int atk = strength;

    // Check if this Actor is wielding a weapon.
    if (weapon != nullptr)
    {
        atk += weapon->get_atk();
    }

    return atk;
}

int Actor::calc_def() const
{
    int def = fortitude;

    // Check if this Actor is wearing armor.
    if (armor != nullptr)
    {
        def += armor->get_def();
    }

    return def;
}

std::string Actor::get_name() const
{
    return name;
}

void Actor::set_name(const std::string& s)
{
    name = s;
}

int Actor::get_hp() const
{
    return hp;
}

void Actor::set_hp(int val)
{
    hp = val;
}

int Actor::get_level() const
{
    return level;
}

void Actor::set_level(int val)
{
    level = val;
}

const std::string& Actor::get_combat_start() const
{
    // Check if we should fall back to the default string.
    if (combat_start.empty())
    {
        static const std::string fallback = "A " + name + " attacks you.";
        return fallback;
    }

    // Else, pick a random entry.
    int entry = rng(0, combat_start.size() - 1);
    return combat_start[entry];
}

const std::string& Actor::get_win_msg() const
{
    // Check if we should fall back to the default string.
    if (win_msg.empty())
    {
        static const std::string fallback = "You defeat the " + name + ".";
        return fallback;
    }

    // Else, pick a random entry.
    int entry = rng(0, win_msg.size() - 1);
    return win_msg[entry];
}

const std::string& Actor::get_lose_msg() const
{
    // Check if we should fall back to the default string.
    if (lose_msg.empty())
    {
        static const std::string fallback = "You are defeated by the " + name + ".";
        return fallback;
    }

    // Else, pick a random entry.
    int entry = rng(0, lose_msg.size() - 1);
    return lose_msg[entry];
}
