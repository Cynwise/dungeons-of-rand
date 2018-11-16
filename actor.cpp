/**
 * @file actor.cpp
 * @brief Generic base class behaviors for Actors.
 */

#include <cassert>
#include <cstdlib>
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

std::unique_ptr<Actor> spawn_actor(const std::string& actor_type)
{
    return std::unique_ptr<Actor>(new Actor(actor_type));
}

Actor::Actor()
{
    // Initialize main stats.
    type = "[NO TYPE]";
    name = "[GENERIC ACTOR]";
    level = 0;
    xp = 0;
    max_hp = 0;
    hp = 0;
    gold = 0;
    encountered = false;

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
    encountered = false;

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
        std::exit(1);
    }

    // Spawn an instance of this type.
    const Actor_Module& parent = *actor_map[actor_type];

    type = actor_type;
    name = parent.name;
    level = parent.level;
    max_hp = parent.max_hp;
    hp = max_hp;
    encountered = false;

    strength = parent.strength;
    fortitude = parent.fortitude;

    attack_list = parent.attack_list;

    combat_start = parent.combat_start;
    win_msg = parent.win_msg;
    lose_msg = parent.lose_msg;

    // Spawn an item from the item drop list.
    if (!parent.item_list.empty())
    {
        const Item_List& item_entry = weighted_element(parent.item_list);
        if (item_entry.type != "none")
        {
            add_item(spawn_item(item_entry.type));
        }
    }

    // Spawn a Weapon from the weapon list.
    if (!parent.weapon_list.empty())
    {
        const Item_List& weapon_entry = weighted_element(parent.weapon_list);
        if (weapon_entry.type != "none")
        {
            weapon.reset(new Weapon(weapon_entry.type));;
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
    if (weapon != nullptr)
    {
        // With weapon.
        if (weapon->attack_list.empty())
        {
            // Use generic attack.
            attack(target, "attack", "attack[s]");
        }
        else
        {
            const std::string& attack_name = random_element(weapon->attack_list);
            Attack_Type* this_attack = attack_map[attack_name];
            const std::string& verb = random_element(this_attack->verbs);
            attack(target, attack_name, verb);
        }
    }
    else
    {
        // No weapon.
        if (attack_list.empty())
        {
            // Use generic attack.
            attack(target, "attack", "attack[s]");
        }
        else
        {
            const std::string& attack_name = random_element(attack_list);
            Attack_Type* this_attack = attack_map[attack_name];
            const std::string& verb = random_element(this_attack->verbs);
            attack(target, attack_name, verb);
        }
    }
}

void Actor::attack(Actor& target, const std::string& attack_name, const std::string& verb)
{
    int atk = 0;
    int damage = 0;

    // Get attack type.
    Attack_Type* this_attack = attack_map[attack_name];

    // Check if weapon attack or intrinsic attack.
    bool weapon_attack = false;
    if (has_weapon())
    {
        for (auto& attack_it : weapon->attack_list)
        {
            if (attack_name == attack_it)
            {
                weapon_attack = true;
                break;
            }
        }
    }

    // Calculate damage.
    if (weapon_attack == true)
    {
        atk = calc_atk() + weapon->get_atk() + this_attack->calc_atk();
    }
    else
    {
        atk = calc_atk() + this_attack->calc_atk();
    }

    damage = roll(2, atk) / 2 + 1;
    int net_damage = target.hurt(damage);

    // Report results.
    if (net_damage > 0)
    {
        this_attack->print_attack(*this, target, verb, net_damage);
    }
    else
    {
        // Report miss.
        const Player& player = Player::get_instance();
        if (this == &player)
        {
            std::cout << "You attempt to attack the ";
            std::cout << target.get_name();
            std::cout << " but they dodge.\n\n";
        }
        else
        {
            std::cout << "The " << name;
            std::cout << " attempts to attack you but you dodge.\n\n";
        }
    }
};

int Actor::hurt(int damage)
{
    // Sanity check. Damage cannot be negative.
    assert(damage >= 0);

    int hp_before = hp;

    // Calculate defense. Net def = (1d(def)-1)/2
    int def = calc_def();
    if (armor != nullptr)
    {
        def += armor->get_def();
    }
    def = roll(2, def) / 2 - 1;

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

    if (weapon != nullptr)
    {
        room.add_item(std::move(weapon));
    }

    if (armor != nullptr)
    {
        room.add_item(std::move(armor));
    }
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

    return atk;
}

int Actor::calc_def() const
{
    int def = fortitude;

    return def;
}

bool Actor::has_weapon() const
{
    if (weapon == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
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

int Actor::get_gold() const
{
    return gold;
}

void Actor::set_gold(int val)
{
    gold = val;
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
