/**
 * @file centaur_room.cpp
 * @brief Implements a basic overloaded room which starts an
 * encounter upon the first enter().
 */

#include <iostream>

#include <actor/player.h>
#include <room/centaur_room.h>

void fight(Actor&);

Centaur_Room::Centaur_Room()
{
    // Set default description for this room type.
    name = "Centaur room";
    description =
        "The room smells like that Centaurs use this room to go number two.";
    brief =
        "This room has a pile of poop that clearly shows signs of"
        "Centaur habitation";
}

Centaur_Room* Centaur_Room::clone()
{
    Centaur_Room* tmp = new Centaur_Room;
    *tmp = *this;
    return tmp;
}

void Centaur_Room::enter()
{
    player_room = this;

    // Check if room has been entered before.
    if (entered == false)
    {
        entered = true;
        std::cout << brief << std::endl;
        std::cout << description << std::endl;

        // Special encounter!
        std::cout << "\nA centaur prances in front of you!\n\n";
        Actor centaur("centaur");
        fight(centaur);
    }
    else
    {
        std::cout << brief << std::endl;
    }
}
