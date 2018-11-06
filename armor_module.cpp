/**
 * @file armor_module.cpp
 */

#include <string>

#include <item.h>
#include <item/armor.h>
#include <rng.h>
#include <armor_module.h>
#include <vendor/json.h>

void from_json(const Json& json, Armor_Module& mod)
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
	
	it = json.find("def");
	if (it != json.end())
	{
		json.at("def").get_to(mod.def);
	}
}

Armor Armor_Module::create()
{
	Armor armor;
	
	armor.type = type;
	armor.name = name;
	
	armor.def = def;
}
