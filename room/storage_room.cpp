/**
 * @file storage_room.cpp
 * @brief Implements a basic overloaded room which starts an
 * encounter upon the first enter().
 */

#include <iostream>

#include <actor/player.h>
#include <actor/barbarian.h>
#include <actor/rat.h>
#include <room/storage_room.h>
#include "rng.h"

void fight(Actor&);

Storage_Room::Storage_Room()
{
    // Set default description for this room type.
    name = "Storage Room";
    description =
        "This old room is full of boxes and cobwebs "
        "that cover them.";
    brief =
        "This room looks like it was used for storage.";
}

Storage_Room* Storage_Room::clone()
{
    Storage_Room* tmp = new Storage_Room;
    *tmp = *this;
    return tmp;
}

void Storage_Room::enter()
{
    player_room = this;

    // Check if room has been entered before.
    if (entered == false)
    {
        entered = true;
        std::cout << brief << std::endl;
        std::cout << description << std::endl;

        // Special encounter!
        int chance = flip();
        if(chance == 1)
        {
            std::cout << "\nA barbarian gets the jump on you!\n\n";
            Barbarian barbarian;
            fight(barbarian);
        }
        else
        {
            std::cout << "\n A rat jumps at you!\n\n";
            Rat rat;
            fight(rat);
        }
    }
    else
    {
        std::cout << brief << std::endl;
    }
}
