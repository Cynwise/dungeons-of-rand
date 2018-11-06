/**
 * @file item_module.cpp
 */

#include <string>

#include <item.h>
#include <rng.h>
#include <item_module.h>
#include <vendor/json.h>

void from_json(const Json& json, Item_Module& mod)
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
}

Item Item_Module::create()
{
	Item item;
	
	item.type = type;
	item.name = name;
}
