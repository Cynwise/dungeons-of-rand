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
}

Weapon Weapon_Module::create()
{
    Weapon weapon;

    weapon.type = type;
    weapon.name = name;

    weapon.atk = atk;
}
