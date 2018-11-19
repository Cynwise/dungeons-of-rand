/**
 * @file room.cpp
 * @brief Generic base class for all environments.
 */

#include <cstdlib>
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
        std::exit(1);
    }

    // Spawn an instance of this Room type.
    Room_Module& parent = *room_map[room_type];

    type = parent.type;
    name = parent.name;
    brief = parent.brief;
    description = parent.description;
    entered = false;

    // Spawn a random Actor from the spawn list.
    if (!parent.actor_spawn.empty())
    {
        const Actor_Spawn& entry = weighted_element(parent.actor_spawn);
        if (entry.type != "none")
        {
            for (size_t i = 0; i < entry.count; ++i)
            {
                actors.push_back(spawn_actor(entry.type));
            }
        }
    }

    // Spawn a random Item from the spawn list.
    if (!parent.item_list.empty())
    {
        const Item_List& entry = weighted_element(parent.item_list);
        if (entry.type != "none")
        {
            items.push_back(spawn_item(entry.type));
        }
    }
}

Room& Room::operator=(const Room& other)
{
    type = other.type;
    name = other.name;
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
    player_room = this;

    // Check if room has been entered before.
    if (entered == false)
    {
        entered = true;
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
    print_paths();
    print_contents();
}

void Room::print_brief()
{
    std::cout << brief << "\n\n";
    print_paths();
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

void Room::print_paths()
{
    // Check if there is nothing to print.
    if (path.size() == 0)
    {
        return;
    }

    auto it = path.find("n");
    if (it != path.end())
    {
        std::cout << "There is a " << path["n"]->get_name();
        if (path["n"]->entered == true)
        {
            std::cout << " (visited)";
        }
        std::cout << " to the north.\n";
    }

    it = path.find("e");
    if (it != path.end())
    {
        std::cout << "There is a " << path["e"]->get_name();
        if (path["e"]->entered == true)
        {
            std::cout << " (visited)";
        }
        std::cout << " to the east.\n";
    }

    it = path.find("s");
    if (it != path.end())
    {
        std::cout << "There is a " << path["s"]->get_name();
        if (path["s"]->entered == true)
        {
            std::cout << " (visited)";
        }
        std::cout << " to the south.\n";
    }

    it = path.find("w");
    if (it != path.end())
    {
        std::cout << "There is a " << path["w"]->get_name();
        if (path["w"]->entered == true)
        {
            std::cout << " (visited)";
        }
        std::cout << " to the west.\n";
    }

    std::cout << std::endl;
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

bool Room::is_safe() const
{
    if (actors.empty())
    {
        return true;
    }
    else
    {
        return false;
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
