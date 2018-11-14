/**
 * @file actor_module.cpp
 */

#include <actor.h>
#include <actor_module.h>
#include <inventory.h>
#include <item_list.h>
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

    it = json.find("item_list");
    if (it != json.end())
    {
        json.at("item_list").get_to(mod.item_list);
    }

    it = json.find("combat_start");
    if (it != json.end())
    {
        json.at("combat_start").get_to(mod.combat_start);
    }

    it = json.find("win");
    if (it != json.end())
    {
        json.at("win").get_to(mod.win_msg);
    }

    it = json.find("lose");
    if (it != json.end())
    {
        json.at("lose").get_to(mod.lose_msg);
    }
}
