/**
 * @file actor_module.cpp
 */

#include <actor.h>
#include <actor_module.h>
#include <inventory.h>
#include <item/armor.h>
#include <item/weapon.h>

void from_json(const Json& json, Actor_Module& mod)
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
    else
    {
        // Fallback to "type" field if no "name" is found.
	mod.name = mod.type;
    }

    it = json.find("level");
    if (it != json.end())
    {
        json.at("level").get_to(mod.level);
    }

    it = json.find("max_hp");
    if (it != json.end())
    {
        json.at("max_hp").get_to(mod.max_hp);
    }

    it = json.find("strength");
    if (it != json.end())
    {
        json.at("strength").get_to(mod.strength);
    }

    it = json.find("fortitude");
    if (it != json.end())
    {
        json.at("fortitude").get_to(mod.fortitude);
    }
}

Actor Actor_Module::create()
{
    Actor actor;

    actor.type = type;
    actor.name = name;
    actor.level = level;
    actor.max_hp = max_hp;
    actor.hp = max_hp;

    actor.strength = strength;
    actor.fortitude = fortitude;

    actor.weapon = nullptr;
    actor.armor = nullptr;

    return actor;
}
