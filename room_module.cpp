/**
 * @file room_module.cpp
 */

#include <string>

#include <actor.h>
#include <rng.h>
#include <room.h>
#include <room_module.h>
#include <vendor/json.h>

void from_json(const Json& json, Room_Module& mod)
{
    auto it = json.find("type");
    if (it != json.end())
    {
        json.at("type").get_to(mod.type);
    }

    it = json.find("name");
    if (it != json.end())
    {
        json.at("name").get_to(mod.name);
    }
    else
    {
        mod.name = mod.type;
    }

    it = json.find("brief");
    if (it != json.end())
    {
        json.at("brief").get_to(mod.brief);
    }

    it = json.find("description");
    if (it != json.end())
    {
        json.at("description").get_to(mod.description);
    }

    it = json.find("actor_spawn");
    if (it != json.end())
    {
        json.at("actor_spawn").get_to(mod.actor_spawn);
    }

    it = json.find("item_list");
    if (it != json.end())
    {
        json.at("item_list").get_to(mod.item_list);
    }
}

void from_json(const Json& json, Actor_Spawn& mod)
{
    auto it = json.find("type");
    if (it != json.end())
    {
        json.at("type").get_to(mod.type);
    }

    it = json.find("chance");
    if (it != json.end())
    {
        json.at("chance").get_to(mod.chance);
    }
    else
    {
        // Fall back to default value.
        mod.chance = 1;
    }

    it = json.find("count");
    if (it != json.end())
    {
        json.at("count").get_to(mod.count);
    }
}
