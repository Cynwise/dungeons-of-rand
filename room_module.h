/**
 * @file room_module.h
 * @brief Defines the structure of loadable Room modules.
 */

#ifndef ROOM_MODULE_H
#define ROOM_MODULE_H

#include <utility>
#include <string>

#include <vendor/json.h>

typedef nlohmann::json Json;

class Room;

/// Stores information about an Actor spawn chance.
class Actor_Spawn
{
public:

    std::string type;
    int count;
};

/// Stores information for a single Room type.
class Room_Module
{
public:

    /// Unique identifier for this Room type.
    std::string type;

private:

    friend class Room;

    friend void from_json(const Json& json, Room_Module& mod);

    std::string name;
    std::string brief;
    std::string description;

    std::vector<Actor_Spawn> actor_spawn;
};

void from_json(const Json& json, Room_Module& mod);
void from_json(const Json& json, Actor_Spawn& mod);

#endif // ROOM_MODULE_H
