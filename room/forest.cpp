/**
 * @file forest.cpp
 * @brief basic room with rando chance to spawn certain enemies
 */

#include <iostream>

#include <actor/player.h>
#include <actor/barbarian.h>
#include <actor/bear.h>
#include <actor/echidna.h>
#include <actor/rat.h>
#include <actor/snake.h>
#include <actor/spider.h>
#include <room/forest.h>
#include <rng.h>

void fight(Actor&);

Forest::Forest()
{
    // Set default description for this room type.
    name = "Forest";
    description =
        "A secluded forest.";
    brief =
        "You see a forest yet you still seem to inside a dungeon. "
        "The ceiling appears to shine artificial light.";
}

Forest* Forest::clone()
{
    Forest* tmp = new Forest;
    *tmp = *this;
    return tmp;
}

void Forest::enter()
{
    player_room = this;

    // Check if room has been entered before.
    if (entered == false)
    {
        entered = true;
        std::cout << brief << std::endl;
        std::cout << description << std::endl;

        int encounter = rng(1,6);
        if(encounter == 1)
        {
            std::cout << "\nA barbarian gets the jump on you!\n\n";
            Barbarian barbarian;
            fight(barbarian);
        }
        else if(encounter == 2)
        {
            std::cout << "\nA rat jumps out from the bushes!\n\n";
            Rat rat;
            fight(rat);
        }
        else if(encounter == 3)
        {
            std::cout << "\nA bear ambushes you!\n\n";
            Bear bear;
            fight(bear);
        }
        else if(encounter == 4)
        {
            std::cout << "\nA spider attacks from above\n\n";
            Spider spider;
            fight(spider);
        }
        else if(encounter == 5)
        {
            std::cout<< "\nA echidna slithers in front of you\n\n";
            Echidna echidna;
            fight(echidna);
        }
        else
        {
            std::cout << "\n A snake sneaks up from behind!\n\n";
            Snake snake;
            fight(snake);
        }

    }
    else
    {
        std::cout << brief << std::endl;
    }
}
