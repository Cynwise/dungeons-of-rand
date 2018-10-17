/**
 * @file dragon_room.cpp
 * @brief Implements a basic overloaded room which starts an
 * encounter upon the first enter().
 */

#include <iostream>

#include <actor/player.h>
#include <actor/dragon.h>
#include <room/dragon_room.h>

void fight(Actor&);

Dragon_Room::Dragon_Room()
{
    // Set default description for this room type.
    name = "Dragon room";
    description =
        "A Cave with lava flowing through the rocks into a pool of lava";
    brief =
        "This room has the perfect temperature for a living and fire breathing"
        "Dragon!!!";
}

Dragon_Room* Dragon_Room::clone()
{
    Dragon_Room* tmp = new Dragon_Room;
    *tmp = *this;
    return tmp;
}

void Dragon_Room::enter()
{
    player_room = this;

    // Check if room has been entered before.
    if (entered == false)
    {
        entered = true;
        std::cout << brief << std::endl;
        std::cout << description << std::endl;

        // Special encounter!
        std::cout << "\nA Dragon flies in Front of You!\n\n";
        Dragon dragon;
        fight(dragon);
    }
    else
    {
        std::cout << brief << std::endl;
    }
}
