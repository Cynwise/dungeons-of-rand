/**
 * @file item_module.h
 * @brief Defines the structure of loadable generic Item modules.
 */

#ifndef ITEM_MODULE_H
#define ITEM_MODULE_H

#include <utility>
#include <string>

#include <vendor/json.h>

typedef nlohmann::json Json;

class Item;

/// Stores information for a single Item type.
class Item_Module
{
public:

    /// Unique identifier for this Item type.
    std::string type;

private:

    // Allows Item to access parameters from the module.
    // Used for Item construction.
    friend class Item;

    friend void from_json(const Json& json, Item_Module& mod);

    std::string name;
};

void from_json(const Json& json, Item_Module& mod);

#endif // ITEM_MODULE_H
