/**
 * @file room.cpp
 * @brief Generic base class for all environments.
 */

#include <iostream>
#include <memory>

#include <actor.h>
#include <actor/player.h>
#include <item.h>
#include <module.h>
#include <rng.h>
#include <room.h>
#include <room_module.h>

// Declare pointer to current room.
Room* player_room;

Room::Room()
{
    name = "[GENERIC ROOM]";
    description = "";
    brief = "";
    entered = false;
}

Room::~Room()
{
    // Actors and Items will be deleted when their vector's are
    // deleted.
}

Room::Room(const std::string& room_type)
{
    // Check if the type exists.
    auto it = room_map.find(room_type);
    if (it == room_map.end())
    {
        std::cerr << "ROOM DOES NOT EXIST: " << room_type << std::endl;
        return;
    }

    // Spawn an instance of this Room type.
    Room_Module& parent = *room_map[room_type];

    type = parent.type;
    brief = parent.brief;
    description = parent.description;

    // Spawn a random Actor from the spawn list.
    if (!parent.actor_spawn.empty())
    {
        // Calculate the sum of Actor spawn chances.
        long sum = 0;
        for (auto actor_it = parent.actor_spawn.begin(); actor_it != parent.actor_spawn.end(); ++actor_it)
        {
            sum += actor_it->chance;
        }

        // Generate a weighted entry value.
        long entry = rng(0, sum);

        // Iterate over the list until we find the first valid entry.
        long weighted_chance = 0;
        for (auto actor_it = parent.actor_spawn.begin(); actor_it != parent.actor_spawn.end(); ++actor_it)
        {
            weighted_chance += actor_it->chance;

            // Spawn the Actor and add it to the Room.
            // Don't spawn an Actor with a chance of 0.
            if (weighted_chance >= entry && actor_it->chance != 0)
            {
                if (actor_it->type == "none")
                {
                    break;
                }

                int actor_count = actor_it->count;

                while (actor_count > 0)
                {
                    std::unique_ptr<Actor> spawned(new Actor(actor_it->type));
                    actors.push_back(std::move(spawned));
                    --actor_count;
                }

                break;
            }
        }
    }

    // Spawn a random Item from the spawn list.
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

            // Spawn the Item and add it to the Room.
            // Don't spawn an Item with a chance of 0 or a type of "none".
            if (weighted_chance >= entry && item_it->chance != 0)
            {
                if (item_it->type == "none")
                {
                    break;
                }

                items.push_back(spawn_item(item_it->type));
                break;
            }
        }
    }
}

Room& Room::operator=(const Room& other)
{
    type = other.type;
    brief = other.brief;
    description = other.description;

    path = other.path;

    // Delete this Room's Actors.
    actors.clear();

    // Copy the other Room's Actors.
    for (auto it = other.actors.begin(); it != other.actors.end(); ++it)
    {
        std::unique_ptr<Actor> actor_clone(new Actor(**it));
        actors.push_back(std::move(actor_clone));
    }

    // Delete this Room's Items.
    items.clear();

    // Copy the other Room's Items.
    for (auto it = other.items.begin(); it != other.items.end(); ++it)
    {
        Item* raw_clone = (*it)->clone();
        std::unique_ptr<Item> item_clone(raw_clone);
        items.push_back(std::move(item_clone));
    }

    return *this;
}

void Room::add_one_way(const std::string& to, Room& dest)
{
    path[to] = &dest;
}

void Room::add_two_way(
    const std::string& to,
    const std::string& back,
    Room& dest)
{
    path[to] = &dest;
    dest.path[back] = this;
}

void Room::enter()
{
    Player& player = Player::get_instance();

    player_room = this;

    // Check if room has been entered before.
    if (entered == false)
    {
        print_full();
    }
    else
    {
        print_brief();
    }
}

void Room::go(const std::string& key)
{
    // Check if destination exists.
    auto it = path.find(key);
    if (it == path.end())
    {
        std::cout << "You can't go there.\n\n";
    }
    else
    {
        // Go to the room.
        Room* destination = it->second;
        destination->enter();
    }
}

void Room::print_full()
{
    std::cout << brief << std::endl;
    std::cout << description << "\n\n";
    print_contents();
}

void Room::print_brief()
{
    std::cout << brief << "\n\n";
    print_contents();
}

void Room::print_contents()
{
    // Check if there is nothing to print.
    if (actors.size() == 0 && items.size() == 0)
    {
        return;
    }

    std::cout << "In this room there is:\n";

    // Print all Actors.
    for (auto it = actors.begin(); it != actors.end(); ++it)
    {
        std::cout << "- a " << (*it)->get_name() << std::endl;
    }

    // Print all items.
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        std::cout << "- a " << (*it)->get_name() << std::endl;
    }

    std::cout << "\n";
}

void Room::add_actor(std::unique_ptr<Actor> actor)
{
    actors.push_back(std::move(actor));
}

Actor* Room::find_actor(const std::string& name)
{
    // Iterate over the list until we find the target actor.
    for (auto it = actors.begin(); it != actors.end(); ++it)
    {
        if (name == (*it)->get_name())
        {
            return it->get();
        }
    }

    // Else, not found.
    return nullptr;
}

std::unique_ptr<Actor> Room::remove_actor(Actor* actor)
{
    std::unique_ptr<Actor> removed = nullptr;

    // Iterate over list until we find the target actor.
    for (auto it = actors.begin(); it != actors.end(); ++it)
    {
        // Check if we found the target.
        if (actor == it->get())
        {
            removed = std::move(*it);
            actors.erase(it);
            break;
        }
    }

    return removed;
}

Item* Room::find_item(const std::string& name)
{
    // Iterate over list until we find the target item.
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        // Check if we found the target.
        if (name == (*it)->get_name())
        {
            return it->get();
        }
    }

    // Else.
    return nullptr;
}

void Room::add_item(std::unique_ptr<Item> item)
{
    items.push_back(std::move(item));
}

std::unique_ptr<Item> Room::remove_item(Item* item)
{
    std::unique_ptr<Item> removed = nullptr;

    // Iterate over list until we find the target item.
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        // Check if we found the target.
        if (item == it->get())
        {
            removed = std::move(*it);
            items.erase(it);
            break;
        }
    }

    return removed;
}

std::string Room::get_name()
{
    return name;
}

void Room::set_name(const std::string& s)
{
    name = s;
}

std::string Room::get_description()
{
    return description;
}

void Room::set_description(const std::string& s)
{
    description = s;
}

std::string Room::get_brief()
{
    return brief;
}

void Room::set_brief(const std::string& s)
{
    brief = s;
}
