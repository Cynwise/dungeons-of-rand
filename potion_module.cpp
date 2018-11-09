/**
 * @file potion_module.cpp
 */

#include <string>

#include <item.h>
#include <item/potion.h>
#include <rng.h>
#include <potion_module.h>
#include <vendor/json.h>

void from_json(const Json& json, Potion_Module& mod)
{
    auto it = json.find("type");
    if (it != json.end())
    {
        json.at("type").get_to(mod.type);
    }

    it = json.find("name");
    if (it != json.end())
    {
        json.at("name").get_to(mod.name);
    }

    it = json.find("stat");
    if (it != json.end())
    {
        json.at("stat").get_to(mod.stat);
    }
}
