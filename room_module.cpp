/**
 * @file room_module.cpp
 */

#include <string>

#include <actor.h>
#include <json.h>
#include <rng.h>
#include <room.h>
#include <room_module.h>

void from_json(const Json& json, Room_Module& mod)
{
    auto it = json.find("type");
    if (it != json.end())
    {
        json.at("type").get_to(mod.type);
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
}

void from_json(const Json& json, Actor_Spawn& mod)
{
    json.at("type").get_to(mod.type);
    json.at("count").get_to(mod.count);
}

Room Room_Module::create()
{
    Room room;

    room.type = type;
    room.brief = brief;
    room.description = description;

    // Spawn a random Actor from the spawn list.
    /// @note Actor_Spawn::count is currently ignored.
    if (!actor_spawn.empty())
    {
        // Pick a random entry.
        int entry = rng(0, actor_spawn.size() - 1);

        // Spawn the Actor and add it to the list.
        std::string actor_type = actor_spawn[entry].type;
        Actor* spawned = new Actor(actor_type);
        room.actors.push_back(spawned);
    }

    return room;
}
