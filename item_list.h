/**
 * @file item_list.h
 * @brief Defines the structure of loadable item lists used in
 * Actor and Room spawning.
 */

#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include <vendor/json.h>

typedef nlohmann::json Json;

/// Stores information about Item drop lists.
class Item_List
{
public:

    std::string type;
    int chance;
};

/// Creates an Item_List from a JSON file.
void from_json(const Json& j, Item_List& mod);

#endif // ITEM_LIST_H
