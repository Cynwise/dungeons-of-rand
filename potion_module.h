/**
 * @file armor_module.h
 * @brief Defines the structure of loadable Armor modules.
 */

#ifndef POTION_MODULE_H
#define POTION_MODULE_H

#include <utility>
#include <string>

#include <vendor/json.h>

typedef nlohmann::json Json;

class Potion;

/// Stores information for a single Armor type.
class Potion_Module
{
public:

    /// Unique identifier for this type.
    std::string type;

private:

    friend class Potion;

    friend void from_json(const Json& json, Potion_Module& mod);

    std::string name;

    int stat;
};

void from_json(const Json& json, Potion_Module& mod);

#endif // POTION_MODULE_H
