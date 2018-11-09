/**
 * @file item_list.cpp
 * @brief Implements the loading of item lists from a json file.
 */

#include <item_list.h>

void from_json(const Json& json, Item_List& mod)
{
    auto it = json.find("type");
    if (it != json.end())
    {
        json.at("type").get_to(mod.type);
    }

    it = json.find("chance");
    if (it != json.end())
    {
        json.at("chance").get_to(mod.chance);
    }
}
