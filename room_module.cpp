/**
 * @file room_module.cpp
 */

#include <string>

#include <actor_spawn.h>
#include <json.h>
#include <room.h>
#include <room_module.h>

void from_json(const Json& json, Room_Module& mod)
{
    mod.type = json["type"];
    mod.brief = json["brief"];
    mod.description = json["description"];
}

Room Room_Module::create()
{
    Room room;

    room.type = type;
    room.brief = brief;
    room.description = description;

    return room;
}
