/**
 * @file barbarian_room.cpp
 * @brief Implements a basic overloaded room which starts an
 * encounter upon the first enter().
 */

#include <iostream>

#include <actor/player.h>
#include <actor/barbarian.h>
#include <room/barbarian_room.h>

void fight(Actor&);

Barbarian_Room::Barbarian_Room()
{
    // Set default description for this room type.
    name = "Barbarian Room";
    description =
        "Barbarians have clearly inhabited this room for some time.";
    brief =
        "This dingy dungeon clearly shows evidence of a "
        "barbarian infestation.";
}

Barbarian_Room* Barbarian_Room::clone()
{
    Barbarian_Room* tmp = new Barbarian_Room;
    *tmp = *this;
    return tmp;
}

void Barbarian_Room::enter()
{
    player_room = this;

    // Check if room has been entered before.
    if (entered == false)
    {
        entered = true;
        std::cout << brief << std::endl;
        std::cout << description << std::endl;

        // Special encounter!
        std::cout << "\nA barbarian gets the jump on you!\n\n";
        Barbarian barbarian;
        fight(barbarian);
    }
    else
    {
        std::cout << brief << std::endl;
    }
}
