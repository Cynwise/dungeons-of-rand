/**
 * @file armor_module.h
 * @brief Defines the structure of loadable Armor modules.
 */

#ifndef ARMOR_MODULE_H
#define ARMOR_MODULE_H

#include <utility>
#include <string>

#include <vendor/json.h>

typedef nlohmann::json Json;

class Armor;

/// Stores information for a single Armor type.
class Armor_Module
{
public:

    /// Spawns an Armor of this type.
    Armor create();

    /// Unique identifier for this type.
    std::string type;

private:

    friend void from_json(const Json& json, Armor_Module& mod);

    std::string name;
    
    int def;
};

void from_json(const Json& json, Armor_Module& mod);

#endif // ARMOR_MODULE_H
