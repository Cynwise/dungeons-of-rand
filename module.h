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

typedef nlohmann::json Json;

/// Map of names to Actors.
typedef std::map<std::string, Actor_Module*> Actor_Map;
extern Actor_Map actor_map;

/// Loads all found modules.
void modules_load();

/// Loads an actor module from path.
void module_load_actor(const std::string& path);

#endif // MODULE_H
