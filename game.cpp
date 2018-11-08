/**
 * @file game.cpp
 * @brief Main entry point for dungeons-of-rand.
 */

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

#include <actor.h>
#include <actor/player.h>
#include <item.h>
#include <item/armor.h>
#include <item/weapon.h>
#include <module.h>
#include <room.h>

#include <rng.h>

/// Main game loop.
int game_loop();

void game_over();
void get_name(std::string& name);
void start(const std::string& name);
void fight(Actor& actor);

int main(int argc, char* argv[])
{
    bool debug = false;

    // Check for debug flag.
    if (argc >= 2)
    {
        std::string first_arg = argv[1];
        if (first_arg == "-d")
        {
            debug = true;
        }
    }

    // Initialize RNG.
    std::srand(std::time(NULL));

    // Load all modules.
    modules_load();

    // Set player name.
    if (debug == false)
    {
        // Prompt user for name.
        std::string player_name;
        get_name(player_name);
        player.set_name(player_name);

        // Prompt to begin.
        start(player_name);
    }
    else
    {
        player.set_name("Tester");
    }

    // Define initial room.
    Room room_1;
    room_1.set_name("Pretty dank dungeon");
    room_1.set_description
    (
        "Very unhygenic.\nA hallway leads to the north."
    );
    room_1.set_brief("This is a very dank dungeon.");

    // Place some sample items in the starting room.
    Weapon stick("stick");
    room_1.add_item(stick);
    Armor rags("peasant_rags");
    room_1.add_item(rags);
    auto potion = spawn_item("small_health_potion");
    room_1.add_item(*potion);

    // Define more rooms.
    Room* last_room = &room_1;
    for (int i = 0; i < 100; ++i)
    {
        Room* next_room;

        // Pick which room type to generate.
        int chance = rng(1, 10);
        if (chance <= 3)
        {
            next_room = new Room("storage_room");
        }
        else if (chance <= 6)
        {
            next_room = new Room("forest");
        }
        else if (chance <= 8)
        {
            next_room = new Room("rat_room");
        }
        else if (chance <= 7)
        {
            next_room = new Room("vendor_room");
        }
        else if (chance <= 9)
        {
            next_room = new Room("treasure_room");
        }
        else
        {
            next_room = new Room("barbarian_room");
        }

        // Link this room.
        last_room->add_two_way("n", "s", *next_room);
        last_room->add_two_way("e", "w", *next_room);
        last_room = next_room;
    }

    // Enter game loop.
    room_1.enter();

    int ret = game_loop();
    return ret;
}

int game_loop()
{
    // User input string.
    std::string input;

    while (1)
    {
        // Get input.
        std::cout << std::endl << "> ";
        std::getline(std::cin, input);
        std::cout << std::endl;

        // Parse input. STUB.
        if (input == "go n" || input == "go north")
        {
            player_room->go("n");
        }
        else if (input == "go e" || input == "go east")
        {
            player_room->go("e");
        }
        else if (input == "go s" || input == "go south")
        {
            player_room->go("s");
        }
        else if (input == "go w" || input == "go west")
        {
            player_room->go("w");
        }
        else if (input == "l" || input == "look")
        {
            player_room->print_full();
        }
        else if (input == "i" || input == "inventory")
        {
            player.print_inventory();
        }
        else if (input == "quit" || input == "q")
        {
            break;
        }
        else if (input.find("take ") == 0)
        {
            // Parse the input.
            size_t pos = input.find(" ") + 1;
            std::string item_name = input.substr(pos);

            // Attempt to find the item.
            Item* origin = player_room->find_item(item_name);

            // Verify that the item was found.
            if (origin == nullptr)
            {
                std::cout << "You can't see a " << item_name;
                std::cout << " in this room.\n";
                continue;
            }
            // Else, move the item.
            std::unique_ptr<Item> item = player_room->remove_item(*origin);
            player.add_item(*item);
            std::cout << "You pick up the " << item->get_name() << std::endl;
        }
        else if (input.find("drop ") == 0)
        {
            // Parse the input.
            size_t pos = input.find(" ") + 1;
            std::string item_name = input.substr(pos);

            // Attempt to remove the item.
            Item* origin = player.find_item(item_name);
            std::unique_ptr<Item> item = player.remove_item(*origin);
            if (item.get() == nullptr)
            {
                std::cout << "No such item could be dropped from your ";
                std::cout << "inventory.\n";
                continue;
            }
            player_room->add_item(*item);
            std:: cout << "You drop the " << item->get_name();
        }
        else if (input.find("use ") == 0)
        {
            // Parse the input.
            size_t pos = input.find(" ") + 1;
            std::string item_name = input.substr(pos);

            // Attempt to find the item.
            Item* item = player.find_item(item_name);
            if (item == nullptr)
            {
                std::cout << "No such item could be found in your inventory.\n";
                continue;
            }

            item->use(player);
        }
        else if (input.find("equip ") == 0)
        {
            // Parse the input.
            size_t pos = input.find(" ") + 1;
            std::string item_name = input.substr(pos);

            // Attempt to find the item.
            Item* item = player.find_item(item_name);
            if (item == nullptr)
            {
                std::cout << "No such item could be found in your inventory.\n";
                continue;
            }

            item->equip(player);
        }
        else if (input == "help")
        {
            std::cout << "Commands:\n\n";
            std::cout << "help: Display this message.\n";
            std::cout << "go [n,e,s,w]: Move in that direction\n";
            std::cout << "look: Inspect your surroundings.\n";
            std::cout << "inventory: Display the contents of your inventory.\n";
            std::cout << "take [item]: Pick up an item.\n";
            std::cout << "drop [item]: Drop an item.\n";
            std::cout << "use [item]: Use an item.\n";
            std::cout << "equip [item]: Equip an item.\n";
            std::cout << "quit: Exit the game.\n";
        }
        else
        {
            // Default.
            std::cout << "Command not recognized. ";
            std::cout << "Enter \"help\" for a basic command list.\n";
        }

        // Check if player died before we loop.
        if (player.get_hp() == 0)
        {
            game_over();
            break;
        }
    }

    return EXIT_SUCCESS;
}

void command_time() {
    std::this_thread::sleep_for(std::chrono::milliseconds(0)); //This works!!
}

void get_name(std::string &name) {
    std::cout << "Please enter the name of your character: \n";
    std::getline(std::cin,name);
    std::cout << "Greetings " << name << "." << std::endl << std::endl;
}

void start(const std::string& name) {
    std::string startingChoice;
    do {
        std::cout << "Well, " << name << " are you ready to begin your adventure? (y/n) \n";
        std::getline(std::cin, startingChoice);
        if(startingChoice == "y") { //yes to adventure
            std::cout << "Then let us begin.\n";
        }
        else if(startingChoice == "n") {    //no loop
            std::cout << "Allow me to ask again... I've got all day.\n\n";
            command_time();

        }
        else {  //input error loop
            std::cout << "Please enter a valid response.. I haven't much patience.\n";
        }
    }
    while(startingChoice != "y");

    command_time();

    std::cout << std::endl;
}

void game_over()
{
    std::cout << "Oh no! Your health has reached 0!\n";
    command_time();
    std::cout << "Game Over\n";
}

void fight(Actor& enemy)
{
    // Loop until someone dies.
    while (1)
    {
        // Player attack turn.
        player.attack(enemy);
        command_time();

        // Check if won.
        if (enemy.get_hp() <= 0)
        {
            std::cout << "You've defeated the " << enemy.get_name() << "!\n";

            break;
        }

        // Enemy attack turn.
        enemy.attack(player);
        command_time();

        // Check if lost.
        if (player.get_hp() <= 0)
        {
            break;
        }
    }
}
