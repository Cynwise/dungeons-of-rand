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

    // Demo combat.
    fight_rat(player);
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
        std::cin >> startingChoice;
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

    std::cout << "----------ACT I----------" << std::endl;
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
            std::cout << "You've defeated " << rat.get_name() << "!\n";
            break;
        }

        // Enemy attack turn.
        rat.attack(actor);
        command_time();

        // Check if lost.
        if (actor.get_hp() <= 0)
        {
            game_over();
            break;
        }
    }
}
