/**
 * @file weapon_module.cpp
 */

#include <string>

#include <item.h>
#include <item/weapon.h>
#include <rng.h>
#include <weapon_module.h>
#include <vendor/json.h>

void from_json(const Json& json, Weapon_Module& mod)
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

    it = json.find("atk");
    if (it != json.end())
    {
        json.at("atk").get_to(mod.atk);
    }

    it = json.find("to_hit");
    if (it != json.end())
    {
        json.at("to_hit").get_to(mod.to_hit);
    }
    else
    {
        // Default value.
        mod.to_hit = 0;
    }

    it = json.find("attack_list");
    if (it != json.end())
    {
        json.at("attack_list").get_to(mod.attack_list);
    }
}
