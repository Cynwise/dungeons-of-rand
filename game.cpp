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
#include <actor/rat.h>
#include <room.h>
#include <room/rat_room.h>

#include <rng.h>

/// Main game loop.
int game_loop();

void game_over();
void get_name(std::string& name);
void start(const std::string& name);
void fight_rat(Actor& actor);

int main(int argc, char* argv[])
{
    // Initialize RNG.
    std::srand(std::time(NULL));

    // Get player name.
    std::string player_name;
    get_name(player_name);
    player.set_name(player_name);

    // Prompt to begin.
    start(player_name);

    // Define initial room.
    Room first_room;
    first_room.set_name("Pretty dank dungeon");
    const std::string first_room_description =
        "This is a very dank dungeon. "
        "Very unhygenic.\nHallways lead to the north and east.";
    first_room.set_description(first_room_description);
    first_room.set_brief("This is a very dank dungeon.");
    first_room.enter();

    int ret = game_loop();
    return ret;
}

int game_loop()
{
    // User input string.
    std::string input;

    // Define second room.
    Room room_2;
    room_2.set_name("Less dank dungeon");
    std::string room_2_description =
        "This is a slightly dank dungeon.\n"
        "You can hear something rustling to the east.";
    room_2.set_description(room_2_description);
    room_2.set_brief("This is a slightly dank dungeon.");

    // Define third room.
    Rat_Room rat_room;

    // Define fourth room.
    Room room_4;
    std::string room_4_description =
        "There is nothing of interest in this room.\n"
        "However, you can hear some rustling to the north.";
    room_4.set_description(room_4_description);
    room_4.set_brief("There is nothing of interest in this room.");

    // Link rooms in a circle.
    player_room->add_path("n", &room_2);
    room_2.add_path("s", player_room);

    room_2.add_path("e", &rat_room);
    rat_room.add_path("w", &room_2);

    rat_room.add_path("s", &room_4);
    room_4.add_path("n", &rat_room);

    room_4.add_path("w", player_room);
    player_room->add_path("e", &room_4);

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
            std::cout << player_room->get_description() << std::endl;
        }
        else if (input == "quit" || input == "q")
        {
            return 0;
        }
        else if (input == "help")
        {
            std::cout << "Commands:\n";
            std::cout << "help: Display this message.\n";
            std::cout << "go [n,e,s,w]: Move in that direction\n";
            std::cout << "look: Inspect your surroundings.\n";
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //This works!!
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
        if(startingChoice == "y") {	//yes to adventure
            std::cout << "Then let us begin.\n";
        }
        else if(startingChoice == "n") {	//no loop
            std::cout << "Allow me to ask again... I've got all day.\n\n";
            command_time();

        }
        else {	//input error loop
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

void fight_rat(Actor& actor)
{
    Rat rat;

    // Loop until someone dies.
    while (1)
    {
        // Player attack turn.
        actor.attack(rat);
        command_time();

        // Check if won.
        if (rat.get_hp() <= 0)
        {
            std::cout << "You've defeated the " << rat.get_name() << "!\n\n";

            // Re-enter the room, just to display brief again.
            player_room->enter();
            break;
        }

        // Enemy attack turn.
        rat.attack(actor);
        command_time();

        // Check if lost.
        if (actor.get_hp() <= 0)
        {
            break;
        }
    }
}
