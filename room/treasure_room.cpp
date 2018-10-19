/**
 * @file treasure_room.cpp
 * @brief Implements a basic overloaded room which will eventually drop an item
 * small chance of encounter upon the first enter().
 */

#include <iostream>

#include <actor/player.h>
#include <room/dragon_room.h>
#include <room/treasure_room.h>
#include "rng.h"

void fight(Actor&);

Treasure_Room::Treasure_Room()
{
    // Set default description for this room type.
    name = "Treasure room";
    description =
        "A room that once held treasure";
    brief =
        "This room once had vast amounts of treasure but now holds nothing."
        "You feel slightly frustrated.";
}

Treasure_Room* Treasure_Room::clone()
{
    Treasure_Room* tmp = new Treasure_Room;
    *tmp = *this;
    return tmp;
}

void Treasure_Room::enter()
{
    player_room = this;

    // Check if room has been entered before.
    if (entered == false)
    {
        entered = true;
        std::cout << brief << std::endl;
        std::cout << description << std::endl;
	
	int encounter = rng(1,50);
        // very small chance a boss will appear
	if(encounter == 50) 
	{
        std::cout << "\nA dragon was gaurding his treasure!\n\n";
        Actor dragon("dragon");
        fight(dragon);
	}
    }
    else
    {
        std::cout << brief << std::endl;
    }
}
