/**
 * @file room.cpp
 * @brief Generic base class for all environments.
 */

#include <iostream>

#include <actor.h>
#include <actor/player.h>
#include <item.h>
#include <module.h>
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

Room::Room(const std::string& type)
{
    // Check if the type exists.
    auto it = room_map.find(type);
    if (it == room_map.end())
    {
        std::cerr << "ROOM DOES NOT EXIST.\n";
        return;
    }

    // Spawn an instance of this Room type.
    *this = room_map[type]->create();
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
        entered = true;
        std::cout << brief << std::endl;
        std::cout << description << std::endl;
    }
    else
    {
        std::cout << brief << std::endl;
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
            break;
        }
        else
        {
            // Else, remove the Actor we just defeated.f
            actors.pop_front();
        }
    }
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
