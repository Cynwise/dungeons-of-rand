/**
 * @file module.cpp
 * @brief Implements module loading.
 */

#include <experimental/filesystem>
#include <fstream>
#include <string>

#include <actor_module.h>
#include <json.h>
#include <module.h>

namespace fs = std::experimental::filesystem;

Actor_Map actor_map;

void modules_load()
{
    fs::recursive_directory_iterator it("data/actor");

    // Iterate until we reach the end of the directory.
    while (it != fs::end(it))
    {
        // Check if this entry is a JSON file.
        if (is_regular_file(*it) && it->path().extension() == ".json")
        {
            const std::string path = it->path();
            module_load_actor(path);
        }

        // Iterate to the next entry.
        it++;
    }
}

void module_load_actor(const std::string& path)
{
    // Load actor module if it can be opened.
    std::ifstream ins(path);
    if (ins.is_open())
    {
        Json json = Json::parse(ins);
        ins.close();

        // Parse the module.
        Actor_Module* mod = new Actor_Module;
        from_json(json, *mod);

        // Insert the module into the actor_modules list.
        actor_map[mod->type] = mod;
    }
}
