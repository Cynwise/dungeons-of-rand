/**
 * @file module.cpp
 * @brief Implements module loading.
 */

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <actor_module.h>
#include <armor_module.h>
#include <attack_type.h>
#include <item_module.h>
#include <module.h>
#include <room_module.h>
#include <vendor/json.h>
#include <weapon_module.h>
#include <potion_module.h>

namespace fs = std::experimental::filesystem;

Actor_Map actor_map;
Attack_Map attack_map;
Room_Map room_map;
Item_Map item_map;
Weapon_Map weapon_map;
Armor_Map armor_map;
Potion_Map potion_map;

void modules_load()
{
    // Load all Actor modules.
    fs::directory_iterator actor_it("data/actor");
    while (actor_it != fs::end(actor_it))
    {
        // Check if this entry is a JSON file.
        if (is_regular_file(*actor_it) && actor_it->path().extension() == ".json")
        {
            const std::string& path = actor_it->path();
            module_load_actor(path);
        }

        // Iterate to the next entry.
        ++actor_it;
    }

    // Load all Attack_Type modules.
    fs::directory_iterator attack_it("data/attack");
    while (attack_it != fs::end(attack_it))
    {
        // Check if this entry is a JSON file.
        if (is_regular_file(*attack_it) && attack_it->path().extension() == ".json")
        {
            const std::string& path = attack_it->path();
            module_load_attack(path);
        }

        // Iterate to the next entry.
        ++attack_it;
    }

    // Load all Room modules.
    fs::directory_iterator room_it("data/room");
    while (room_it != fs::end(room_it))
    {
        // Check if this entry is a JSON file.
        if (is_regular_file(*room_it) && room_it->path().extension() == ".json")
        {
            const std::string& path = room_it->path();
            module_load_room(path);
        }

        // Iterate to the next entry.
        ++room_it;
    }

    // Load all generic Item modules.
    fs::directory_iterator item_it("data/item");
    while (item_it != fs::end(item_it))
    {
        // Check if this entry is a JSON file.
        if (is_regular_file(*item_it) && item_it->path().extension() == ".json")
        {
            const std::string& path = item_it->path();
            module_load_item(path);
        }

        // Iterate to the next entry.
        ++item_it;
    }

    // Load all Weapon modules.
    fs::directory_iterator weapon_it("data/item/weapon");
    while (weapon_it != fs::end(weapon_it))
    {
        // Check if this entry is a JSON file.
        if (is_regular_file(*weapon_it) && weapon_it->path().extension() == ".json")
        {
            const std::string& path = weapon_it->path();
            module_load_weapon(path);
        }

        // Iterate to the next entry.
        ++weapon_it;
    }

    // Load all Armor modules.
    fs::directory_iterator armor_it("data/item/armor");
    while (armor_it != fs::end(armor_it))
    {
        // Check if this entry is a JSON file.
        if (is_regular_file(*armor_it) && armor_it->path().extension() == ".json")
        {
            const std::string& path = armor_it->path();
            module_load_armor(path);
        }

        // Iterate to the next entry.
        ++armor_it;
    }
    // Load all Potion modules.
    fs::directory_iterator potion_it("data/item/potion");
    while (potion_it != fs::end(potion_it))
    {
        // Check if this entry is a JSON file.
        if (is_regular_file(*potion_it) && potion_it->path().extension() == ".json")
        {
            const std::string& path = potion_it->path();
            module_load_potion(path);
        }

        // Iterate to the next entry.
        ++potion_it;
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
    else
    {
        std::cerr << "Error loading module " << path << std::endl;
    }
}

void module_load_attack(const std::string& path)
{
    // Load Attack_Type module if it can be opened.
    std::ifstream ins(path);
    if (ins.is_open())
    {
        Json json = Json::parse(ins);
        ins.close();

        // Parse the module.
        Attack_Type* mod = new Attack_Type;
        *mod = json;

        // Insert the module into the actor_modules list.
        attack_map[mod->type] = mod;
    }
    else
    {
        std::cerr << "Error loading module " << path << std::endl;
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
    else
    {
        std::cerr << "Error loading module " << path << std::endl;
    }
}

void module_load_item(const std::string& path)
{
    // Load Item module if it can be opened.
    std::ifstream ins(path);
    if (ins.is_open())
    {
        Json json = Json::parse(ins);
        ins.close();

        // Parse the module.
        Item_Module* mod = new Item_Module;
        *mod = json;

        // Insert the module into the Item_Module list.
        item_map[mod->type] = mod;
    }
    else
    {
        std::cerr << "Error loading module " << path << std::endl;
    }
}

void module_load_weapon(const std::string& path)
{
    // Load Weapon module if it can be opened.
    std::ifstream ins(path);
    if (ins.is_open())
    {
        Json json = Json::parse(ins);
        ins.close();

        // Parse the module.
        Weapon_Module* mod = new Weapon_Module;
        *mod = json;

        // Insert the module into the Weapon_Module lists.
        weapon_map[mod->type] = mod;
    }
    else
    {
        std::cerr << "Error loading module " << path << std::endl;
    }
}

void module_load_armor(const std::string& path)
{
    // Load Armor module if it can be opened.
    std::ifstream ins(path);
    if (ins.is_open())
    {
        Json json = Json::parse(ins);
        ins.close();

        // Parse the module.
        Armor_Module* mod = new Armor_Module;
        *mod = json;

        // Insert the module into the Armor_Module lists.
        armor_map[mod->type] = mod;
    }
    else
    {
        std::cerr << "Error loading module " << path << std::endl;
    }
}
void module_load_potion(const std::string& path)
{
    // Load Potion module if it can be opened.
    std::ifstream ins(path);
    if (ins.is_open())
    {
        Json json = Json::parse(ins);
        ins.close();

        // Parse the module.
        Potion_Module* mod = new Potion_Module;
        *mod = json;

        // Insert the module into the Potion_Module lists.
        potion_map[mod->type] = mod;
    }
    else
    {
        std::cerr << "Error loading module " << path << std::endl;
    }
}
