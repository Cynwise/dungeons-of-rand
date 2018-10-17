/**
 * @file rat_room.cpp
 * @brief Implements a basic overloaded room which starts an
 * encounter upon the first enter().
 */

#include <iostream>

#include <actor/player.h>
#include <room/rat_room.h>

void fight(Actor&);

Rat_Room::Rat_Room()
{
    // Set default description for this room type.
    name = "Rat Room";
    description =
        "Rats have clearly inhabited this room for some time.";
    brief =
        "This dingy dungeon clearly shows evidence of a "
        "rat infestation.";
}

Rat_Room* Rat_Room::clone()
{
    Rat_Room* tmp = new Rat_Room;
    *tmp = *this;
    return tmp;
}

void Rat_Room::enter()
{
    player_room = this;

    // Check if room has been entered before.
    if (entered == false)
    {
        entered = true;
        std::cout << brief << std::endl;
        std::cout << description << std::endl;

        // Special encounter!
        std::cout << "\nA rat gets the jump on you!\n\n";
        Actor rat("rat");
        fight(rat);
    }
    else
    {
        std::cout << brief << std::endl;
    }
}
