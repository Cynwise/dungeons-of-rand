/**
 * @file module.cpp
 * @brief Implements module loading.
 */

#include <experimental/filesystem>
#include <fstream>
#include <string>

#include <actor_module.h>
#include <module.h>
#include <room_module.h>
#include <vendor/json.h>

namespace fs = std::experimental::filesystem;

Actor_Map actor_map;
Room_Map room_map;

void modules_load()
{
    // Load all Actor modules.
    fs::recursive_directory_iterator actor_it("data/actor");
    while (actor_it != fs::end(actor_it))
    {
        // Check if this entry is a JSON file.
        if (is_regular_file(*actor_it) && actor_it->path().extension() == ".json")
        {
            const std::string path = actor_it->path();
            module_load_actor(path);
        }

        // Iterate to the next entry.
        actor_it++;
    }

    // Load all Room modules.
    fs::recursive_directory_iterator room_it("data/room");
    while (room_it != fs::end(room_it))
    {
        // Check if this entry is a JSON file.
        if (is_regular_file(*room_it) && room_it->path().extension() == ".json")
        {
            const std::string path = room_it->path();
            module_load_room(path);
        }

        // Iterate to the next entry.
        room_it++;
    }
}

void module_load_actor(const std::string& path)
{
    // Load Actor module if it can be opened.
    std::ifstream ins(path);
    if (ins.is_open())
    {
        Json json = Json::parse(ins);
        ins.close();

        // Parse the module.
        Actor_Module* mod = new Actor_Module;
        *mod = json;

        // Insert the module into the actor_modules list.
        actor_map[mod->type] = mod;
    }
}

void module_load_room(const std::string& path)
{
    // Load Room module if it can be opened.
    std::ifstream ins(path);
    if (ins.is_open())
    {
        Json json = Json::parse(ins);
        ins.close();

        // Parse the module.
        Room_Module* mod = new Room_Module;
        *mod = json;

        // Insert the module into the room_modules list.
        room_map[mod->type] = mod;
    }
}
