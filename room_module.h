/**
 * @file room_module.h
 * @brief Defines the structure of loadable Room modules.
 */

#ifndef ROOM_MODULE_H
#define ROOM_MODULE_H

#include <string>

#include <actor_spawn.h>
#include <json.h>

typedef nlohmann::json Json;

class Room;

/// Stores information for a single Room type.
class Room_Module
{
public:

    /// Creates a Room of this type.
    Room create();

    /// Unique identifier for this Room type.
    std::string type;

private:

    friend void from_json(const Json& j, Room_Module& mod);

    std::string name;
    std::string brief;
    std::string description;

    Actor_Spawn actor_spawn;
};

#endif // ROOM_MODULE_H
