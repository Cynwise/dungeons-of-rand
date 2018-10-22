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
    json.at("type").get_to(mod.type);
    json.at("level").get_to(mod.level);
    json.at("max_hp").get_to(mod.max_hp);

    json.at("strength").get_to(mod.strength);
    json.at("fortitude").get_to(mod.fortitude);
}

Actor Actor_Module::create()
{
    Actor actor;

    actor.type = type;
    actor.name = type;
    actor.level = level;
    actor.max_hp = max_hp;
    actor.hp = max_hp;

    actor.strength = strength;
    actor.fortitude = fortitude;

    actor.weapon = nullptr;
    actor.armor = nullptr;

    return actor;
}
