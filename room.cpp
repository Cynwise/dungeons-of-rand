/**
 * @file room.cpp
 * @brief Generic base class for all environments.
 */

#include <iostream>

#include <actor.h>
#include <item.h>
#include <room.h>

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

Room* Room::clone()
{
    Room* tmp = new Room;
    *tmp = *this;
    return tmp;
}

bool Room::add_path(const std::string& entrance, Room* destination)
{
    // Check if entrance is already used.
    auto it = path.find(entrance);
    if (it != path.end())
    {
        // Failure.
        std::cout << "Failed to add path\n.";
        return false;
    }

    // Else, add path.
    path[entrance] = destination;
    return true;
}

void Room::enter()
{
    player_room = this;

    // Check if room has been entered before.
    if (entered == false)
    {
        entered = true;
        std::cout << description << std::endl;
    }
    else
    {
        std::cout << brief << std::endl;
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
