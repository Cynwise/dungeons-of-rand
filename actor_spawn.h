/**
 * @file actor_spawn.h
 * @brief Defines format for Actor spawn entries in rooms.
 */

#ifndef ACTOR_SPAWN_H
#define ACTOR_SPAWN_H

#include <string>
#include <utility>
#include <vector>

#include <json.h>

typedef nlohmann::json Json;

/// Defines Actor-count pair.
typedef std::pair<std::string, int> Actor_Spawn_Entry;

class Actor_Spawn
{
public:

    std::vector<Actor_Spawn_Entry> entries;

    friend void from_json(const Json& j, Actor_Spawn& mod);
};

void from_json(const Json& j, Actor_Spawn& mod);

#endif // ACTOR_SPAWN_H
