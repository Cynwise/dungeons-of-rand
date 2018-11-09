/**
 * @file module.h
 * @brief Handles loadable modules.
 */

#ifndef MODULE_H
#define MODULE_H

#include <map>
#include <string>

#include <vendor/json.h>

class Actor_Module;
class Room_Module;
class Item_Module;
class Weapon_Module;
class Armor_Module;
class Potion_Module;

typedef nlohmann::json Json;

/// Map of names to Actor types.
typedef std::map<std::string, Actor_Module*> Actor_Map;
extern Actor_Map actor_map;

/// Map of names to Room types.
typedef std::map<std::string, Room_Module*> Room_Map;
extern Room_Map room_map;

/// Map of names to Item types (weapons and armor included).
typedef std::map<std::string, Item_Module*> Item_Map;
extern Item_Map item_map;

/// Map of names to Weapon types.
typedef std::map<std::string, Weapon_Module*> Weapon_Map;
extern Weapon_Map weapon_map;

/// Map of names to Armor types.
typedef std::map<std::string, Armor_Module*> Armor_Map;
extern Armor_Map armor_map;

/// Map of names to Potion types.
typedef std::map<std::string, Potion_Module*> Potion_Map;
extern Potion_Map potion_map;

/// Loads all found modules.
void modules_load();

/// Loads an Actor module from path.
void module_load_actor(const std::string& path);

/// Loads a Room module from path.
void module_load_room(const std::string& path);

/// Loads a generic Item module from path.
void module_load_item(const std::string& path);

/// Loads a Weapon module from path.
void module_load_weapon(const std::string& path);

/// Loads an Armor module from path.
void module_load_armor(const std::string& path);

/// Loads a Potion module from path.
void module_load_potion(const std::string& path);

#endif // MODULE_H
