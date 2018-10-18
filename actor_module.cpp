/**
 * @file actor_module.cpp
 */

#include <actor.h>
#include <actor_module.h>
#include <inventory.h>

void from_json(const Json& json, Actor_Module& mod)
{
    mod.type = json["type"];
    mod.level = json["level"];
    mod.max_hp = json["max_hp"];

    mod.strength = json["strength"];
    mod.fortitude = json["fortitude"];
}

Actor Actor_Module::spawn()
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
