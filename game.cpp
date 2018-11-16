/**
 * @file game.cpp
 * @brief Main entry point for dungeons-of-rand.
 */

#include <cctype>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <regex>
#include <thread>

#include <actor.h>
#include <actor/player.h>
#include <attack_type.h>
#include <item.h>
#include <item/armor.h>
#include <item/weapon.h>
#include <module.h>
#include <room.h>
#include <rng.h>

/// Main game loop.
int game_loop();

/// Player command handler.
void player_turn();

/// Make enemy attack the player.
void enemy_turn(Actor& actor);

/// Make player attack on enemy.
bool player_attack(const std::string& enemy_name);
bool player_attack(const std::string& enemy_name, const std::string& verb);

void game_over();
void get_name(std::string& name);
void start(const std::string& name);

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

    // Get player singleton.
    Player& player = Player::get_instance();

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
    room_1.add_item(spawn_item("stick"));
    room_1.add_item(spawn_item("peasant_rags"));
    room_1.add_item(spawn_item("small_health_potion"));

    // Define more rooms.
    Room* last_room = &room_1;
    for (int i = 0; i < 5000; ++i)
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
    Player& player = Player::get_instance();

    while (1)
    {
        // Let the player take a turn.
        player_turn();

        // Let each enemy take a turn.
        auto& actor_list = player_room->actors;
        for (auto it = actor_list.begin(); it != actor_list.end(); ++it)
        {
            auto& enemy = **it;
            enemy_turn(enemy);

            // Check if player died before we loop.
            if (player.get_hp() == 0)
            {
                break;
            }
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

void player_turn()
{
    Player& player = Player::get_instance();
    std::string input = "";

    while (1)
    {
        // Get and handle input.
        std::cout << "> ";
        std::getline(std::cin, input);
        std::cout << std::endl;

        // Parse input. STUB.
        if (input == "go n" || input == "go north")
        {
            if (!player_room->is_safe())
            {
                std::cout << "You can't do that with enemies nearby.\n\n";
            }
            else
            {
                player_room->go("n");
                if (flip())
                {
                    break;
                }
            }
        }
        else if (input == "go e" || input == "go east")
        {
            if (!player_room->is_safe())
            {
                std::cout << "You can't do that with enemies nearby.\n\n";
            }
            else
            {
                player_room->go("e");
                if (flip())
                {
                    break;
                }
            }
        }
        else if (input == "go s" || input == "go south")
        {
            if (!player_room->is_safe())
            {
                std::cout << "You can't do that with enemies nearby.\n\n";
            }
            else
            {
                player_room->go("s");
                if (flip())
                {
                    break;
                }
            }
        }
        else if (input == "go w" || input == "go west")
        {
            if (!player_room->is_safe())
            {
                std::cout << "You can't do that with enemies nearby.\n\n";
            }
            else
            {
                player_room->go("w");
                if (flip())
                {
                    break;
                }
            }
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
            std::exit(EXIT_SUCCESS);
        }
        else if (input == "status" || input == "s")
        {
            player.print_status();
        }
        else if (input.find("attack ") == 0 || input.find("a ") == 0)
        {
            // Parse the input.
            size_t pos = input.find(" ") + 1;
            std::string enemy_name = input.substr(pos);

            bool done = player_attack(enemy_name);
            if (done)
            {
                break;
            }
        }
        else if (input == "attack" || input == "a")
        {
            // Find an enemy to attack.
            if (player_room->actors.empty())
            {
                std::cout << "There are no enemies to attack.\n\n";
            }
            else
            {
                auto& enemy = player_room->actors.front();
                player_attack(enemy->get_name());
                break;
            }
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
                std::cout << " in this room.\n\n";
            }
            else
            {
                // Else, move the item.
                std::unique_ptr<Item> item = player_room->remove_item(origin);
                std::cout << "You pick up the " << item->get_name() << ".\n\n";
                player.add_item(std::move(item));
                break;
            }
        }
        else if (input.find("drop ") == 0)
        {
            // Parse the input.
            size_t pos = input.find(" ") + 1;
            std::string item_name = input.substr(pos);

            // Attempt to remove the item.
            Item* origin = player.find_item(item_name);
            std::unique_ptr<Item> item = player.remove_item(origin);
            if (item.get() == nullptr)
            {
                std::cout << "No such item could be dropped from your ";
                std::cout << "inventory.\n\n";
            }
            else
            {
                std:: cout << "You drop the " << item->get_name() << ".\n\n";
                player_room->add_item(std::move(item));
                break;
            }
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
                std::cout << "No such item could be found in your inventory.\n\n";
            }
            else
            {
                item->use(player);
                break;
            }
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
                std::cout << "No such item could be found in your inventory.\n\n";
            }
            else
            {
                item->equip(player);
                break;
            }
        }
        else if (input.find("check ") == 0)
        {
            // Parse the input.
            size_t pos = input.find(" ") + 1;
            std::string item_name = input.substr(pos);

            // Attempt to find the item.
            Item* item = player.find_item(item_name);
            if (item == nullptr)
            {
                std::cout << "No such item could be found in your inventory.\n\n";
            }
            else
            {
                item->check(player);
                break;
            }
        }
        else if (input == "attacks")
        {
            std::cout << "Attacks:\n\n";

            // Combine intrinsic and weapon attack lists.
            std::vector<std::string> attack_list = player.attack_list;
            if (player.has_weapon())
            {
                for (auto& attack_it : player.weapon->attack_list)
                {
                    attack_list.push_back(attack_it);
                }
            }

            // Iterate over attack list.
            for (auto& attack_name : attack_list)
            {
                auto& attack_type = *attack_map[attack_name];

                // Iterate over verbs.
                for (auto& attack_verb : attack_type.verbs)
                {
                    // Remove macros.
                    std::cout << strip_verb(attack_verb) << "  ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        else if (input == "help")
        {
            std::cout << "Commands:\n\n";
            std::cout << "help:\tDisplay this message.\n";
            std::cout << "go [n,e,s,w]:\tMove in that direction\n";
            std::cout << "look:\tInspect your surroundings.\n";
            std::cout << "attack [enemy]:\tAttack an enemy in the room.\n";
            std::cout << "attacks:\tPrint list of possible attacks.\n";
            std::cout << "status:\tCheck your current status.\n";
            std::cout << "inventory:\tDisplay the contents of your inventory.\n";
            std::cout << "take [item]:\tPick up an item.\n";
            std::cout << "drop [item]:\tDrop an item.\n";
            std::cout << "use [item]:\tUse an item.\n";
            std::cout << "equip [item]:\tEquip an item.\n";
            std::cout << "check [item]:\tCheck an item.\n";
            std::cout << "quit:\tExit the game.\n\n";
        }
        else
        {
            // Check if this is a valid command.
            size_t verb_end = input.find(" ");
            if (verb_end == std::string::npos)
            {
                std::cout << "Syntax not recognized.\n";
                std::cout << "Enter \"help\" for a basic command list.\n\n";
                continue;
            }

            // Check if there is a valid argument to this verb.
            if (input.length() - verb_end <= 1)
            {
                std::cout << "Syntax not recognized.\n";
                std::cout << "Enter \"help\" for a basic command list.\n\n";
                continue;
            }

            // Get verb.
            std::string input_verb = input.substr(0, verb_end);

            // Get enemy name.
            std::string enemy_name = input.substr(verb_end + 1);

            bool done = player_attack(enemy_name, input_verb);
            if (done)
            {
                break;
            }
        }

        // Check if player died before we loop.
        if (player.get_hp() == 0)
        {
            game_over();
            break;
        }
    }
}

void command_time() {
    std::this_thread::sleep_for(std::chrono::milliseconds(0)); //This works!!
}

void get_name(std::string &name) {
    std::cout << "Please enter the name of your character: \n";
    std::getline(std::cin,name);
    std::cout << "Greetings " << name << ".\n\n";
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
    std::cout << "Game Over\n";
}

bool player_attack(const std::string& enemy_name)
{
    Player& player = Player::get_instance();

    // Attempt to find the enemy.
    Actor* enemy = player_room->find_actor(enemy_name);

    // Verify that the enemy was found.
    if (enemy == nullptr)
    {
        std::cout << "You can't see a " << enemy_name;
        std::cout << " in this room.\n\n";
        return false;
    }

    player.attack(*enemy);

    // Check if the enemy died.
    if (enemy->get_hp() == 0)
    {
        std::cout << enemy->get_win_msg() << "\n\n";

        // Dump inventory.
        enemy->dump_items(*player_room);

        // Always drop a corpse.
        auto corpse = spawn_item("corpse");
        std::string corpse_name = enemy->get_name() + " corpse";
        corpse->set_name(corpse_name);
        player_room->add_item(std::move(corpse));
        player_room->remove_actor(enemy);

        // Redisplay room contents.
        player_room->print_contents();
    }

    return true;
}

bool player_attack(const std::string& enemy_name, const std::string& input_verb)
{
    Player& player = Player::get_instance();

    // Combine intrinsic and weapon attack lists.
    std::vector<std::string> attack_list = player.attack_list;
    if (player.has_weapon())
    {
        for (auto& attack_it : player.weapon->attack_list)
        {
            attack_list.push_back(attack_it);
        }
    }

    // Check attack list.
    for (auto& attack_name : attack_list)
    {
        auto& attack_type = *attack_map[attack_name];

        // Check verb list.
        for (auto& attack_verb : attack_type.verbs)
        {
            if (input_verb == strip_verb(attack_verb))
            {
                // Attempt to find the enemy.
                Actor* enemy = player_room->find_actor(enemy_name);

                // Verify that the enemy was found.
                if (enemy == nullptr)
                {
                    std::cout << "You can't see a " << enemy_name;
                    std::cout << " in this room.\n\n";
                    return false;
                }
                else
                {
                    player.attack(*enemy, attack_name, input_verb);

                    // Check if the enemy died.
                    if (enemy->get_hp() == 0)
                    {
                        std::cout << enemy->get_win_msg() << "\n\n";

                        // Dump inventory.
                        enemy->dump_items(*player_room);

                        // Always drop a corpse.
                        auto corpse = spawn_item("corpse");
                        std::string corpse_name = enemy->get_name() + " corpse";
                        corpse->set_name(corpse_name);
                        player_room->add_item(std::move(corpse));
                        player_room->remove_actor(enemy);

                        // Redisplay room contents.
                        player_room->print_contents();
                    }

                    return true;
                }
            }
        }
    }

    std::cout << "Command not recognized.\n";
    std::cout << "Enter \"help\" for a basic command list.\n\n";

    return false;
}

void enemy_turn(Actor& enemy)
{
    Player& player = Player::get_instance();

    // Display combat start message if this is the beginning of combat.
    if (enemy.encountered == false)
    {
        enemy.encountered = true;
        std::cout << enemy.get_combat_start() << "\n\n";
    }

    // Enemy attack turn.
    enemy.attack(player);

    // Check if player lost.
    if (player.get_hp() <= 0)
    {
        std::cout << enemy.get_lose_msg() << "\n\n";
    }
}
