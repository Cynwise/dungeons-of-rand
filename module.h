/**
 * @file module.h
 * @brief Handles loadable modules.
 */

#ifndef MODULE_H
#define MODULE_H

#include <map>
#include <string>

#include <json.h>

class Actor_Module;
class Room_Module;

typedef nlohmann::json Json;

/// Map of names to Actor types.
typedef std::map<std::string, Actor_Module*> Actor_Map;
extern Actor_Map actor_map;

/// Map of names to Room types.
typedef std::map<std::string, Room_Module*> Room_Map;
extern Room_Map room_map;

/// Loads all found modules.
void modules_load();

/// Loads an Actor module from path.
void module_load_actor(const std::string& path);

/// Loads a Room module from path.
void module_load_room(const std::string& path);

#endif // MODULE_H
