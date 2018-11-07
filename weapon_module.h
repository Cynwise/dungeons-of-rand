/**
 * @file weapon_module.h
 * @brief Defines the structure of loadable Weapon modules.
 */

#ifndef WEAPON_MODULE_H
#define WEAPON_MODULE_H

#include <utility>
#include <string>

#include <vendor/json.h>

typedef nlohmann::json Json;

class Weapon;

/// Stores information for a single Item type.
class Weapon_Module
{
public:

    /// Unique identifier for this Item type.
    std::string type;

private:

    friend class Weapon;

    friend void from_json(const Json& json, Weapon_Module& mod);

    std::string name;

    int atk;
};

void from_json(const Json& json, Weapon_Module& mod);

#endif // WEAPON_MODULE_H
