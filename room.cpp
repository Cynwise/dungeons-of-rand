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

extern void fight(Actor& target);

Room::Room()
{
    name = "[GENERIC ROOM]";
    description = "";
    brief = "";
    entered = false;
}

Room::~Room()
{
    std::list<Actor*>::iterator it_actors = actors.begin();
    std::list<Item*>::iterator it_items = items.begin();

    // Delete all dynamically allocated objects.
    while (it_actors != actors.end())
    {
        delete *it_actors;
        ++it_actors;
    }
    while (it_items != items.end())
    {
        delete *it_items;
        ++it_items;
    }
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
        // Pick a random entry.
        int entry = rng(0, parent.actor_spawn.size() - 1);

        // Spawn the Actor and add it to the list.
        std::string actor_type = parent.actor_spawn[entry].type;
        int actor_count = parent.actor_spawn[entry].count;
        while (actor_count > 0)
        {
            Actor* spawned = new Actor(actor_type);
            actors.push_back(spawned);
            actor_count--;
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
    for (auto it = actors.begin(); it != actors.end(); ++it)
    {
        delete *it;
    }
    actors.clear();

    // Copy the other Room's Actors.
    for (auto it = other.actors.begin(); it != other.actors.end(); ++it)
    {
        Actor* tmp = new Actor;
        *tmp = **it;
        actors.push_back(tmp);
    }

    // Delete this Room's Items.
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        delete *it;
    }
    items.clear();

    // Copy the other Room's Items.
    for (auto it = other.items.begin(); it != other.items.end(); ++it)
    {
        Item* tmp = (*it)->clone();
        items.push_back(tmp);
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

    // Check if there is no additional info to display.
    if (actors.empty())
    {
        return;
    }

    // Fight until are enemies in the room are dead.
    while (!actors.empty())
    {
        Actor* enemy = actors.front();
        std::cout << "\nA " << enemy->get_name() << " attacks you!\n\n";
        fight(*enemy);

        // Break if the player died.
        if (player.get_hp() == 0)
        {
            return;
        }
        else
        {
            // Else, dump the defeated enemies inventory into the room
            // and remove the Actor we just defeated.
            enemy->dump_items(*this);

            // Always drop a corpse.
            Item corpse("corpse");
            std::string corpse_name = enemy->get_name() + " corpse";
            corpse.set_name(corpse_name);
            player_room->add_item(corpse);

            actors.pop_front();
        }
    }

    // Redraw room message if combat occurred.
    print_brief();
}

void Room::go(const std::string& key)
{
    // Check if destination exists.
    auto it = path.find(key);
    if (it == path.end())
    {
        std::cout << "You can't go there.\n";
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
    std::cout << description << std::endl;
    print_contents();
}

void Room::print_brief()
{
    std::cout << brief << std::endl;
    print_contents();
}

void Room::print_contents()
{
    // Check if there is nothing to print.
    if (actors.size() == 0 && items.size() == 0)
    {
        return;
    }

    std::cout << "\nIn this room there is:\n";

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
}

void Room::add_actor(const Actor& actor)
{
    actors.push_back(new Actor(actor));
}

std::unique_ptr<Actor> Room::remove_actor(const Actor& actor)
{
    std::unique_ptr<Actor> removed = nullptr;

    // Iterate over list until we find the target actor.
    for (auto it = actors.begin(); it != actors.end(); ++it)
    {
        // Check if we found the target.
        if (&actor == *it)
        {
            removed.reset(*it);
            actors.erase(it);
            break;
        }
    }

    return removed;
}

Item* Room::find_item(const std::string& name)
{
    // Iterate over list until we find the target actor.
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        // Check if we found the target.
        if (name == (*it)->get_name())
        {
            return *it;
        }
    }

    // Else.
    return nullptr;
}

void Room::add_item(const Item& item)
{
    items.push_back(item.clone());
}

std::unique_ptr<Item> Room::remove_item(const Item& item)
{
    std::unique_ptr<Item> removed = nullptr;

    // Iterate over list until we find the target item.
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        // Check if we found the target.
        if (&item == *it)
        {
            removed.reset(*it);
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
