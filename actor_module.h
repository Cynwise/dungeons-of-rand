/**
 * @file actor_module.h
 * @brief Defines the structure of loadable Actor modules.
 */

#ifndef ACTOR_MODULE_H
#define ACTOR_MODULE_H

#include <string>

#include <vendor/json.h>

typedef nlohmann::json Json;

class Actor;

/// Stores information for a single Actor type.
class Actor_Module
{
public:

    /// Spawns an actor of this type.
    Actor create();

    /// Unique identifier for this Actor type;
    std::string type;

private:

    friend void from_json(const Json& j, Actor_Module& mod);

    std::string name;
    int level;
    int xp;
    int max_hp;

    int strength;
    int fortitude;
};

/// Creates an actor module from a JSON file.
void from_json(const Json& j, Actor_Module& mod);

#endif // ACTOR_MODULE_H
