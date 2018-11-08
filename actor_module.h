/**
 * @file actor_module.h
 * @brief Defines the structure of loadable Actor modules.
 */

#ifndef ACTOR_MODULE_H
#define ACTOR_MODULE_H

#include <string>
#include <vector>

#include <vendor/json.h>

typedef nlohmann::json Json;

class Actor;

/// Stores information about Item drop lists.
class Item_List
{
public:

    std::string type;
    int chance;
};

/// Stores information for a single Actor type.
class Actor_Module
{
public:

    /// Unique identifier for this Actor type;
    std::string type;

private:

    friend class Actor;

    friend void from_json(const Json& j, Actor_Module& mod);

    std::string name;
    int level;
    int xp;
    int max_hp;

    int strength;
    int fortitude;

    std::vector<Item_List> item_list;
};

/// Creates an actor module from a JSON file.
void from_json(const Json& j, Actor_Module& mod);
void from_json(const Json& j, Item_List& mod);

#endif // ACTOR_MODULE_H
