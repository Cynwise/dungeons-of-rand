/**
 * @file room.h
 * @brief Generic base class for all environments. Also declare
 * global pointer to current room.
 */

#ifndef ROOM_H
#define ROOM_H

#include <list>
#include <map>
#include <string>

class Actor;
class Item;
class Room;

/// Maps input strings to paths to other rooms.
typedef std::map<std::string, Room*> Path;

/// Generic base class for all environments.
class Room
{
public:

    Room();

    virtual ~Room();

    virtual Room* clone();

    /// Add a path from this room.
    bool add_path(const std::string& entrance, Room* destination);

    /// Call to enter this room.
    virtual void enter();

    /// Go to different room by path.
    virtual void go(const std::string& key);

    // Getters/setters.
    std::string get_name();
    void set_name(const std::string& s);
    std::string get_description();
    void set_description(const std::string& s);
    std::string get_brief();
    void set_brief(const std::string& s);

protected:

    /// Name of current room.
    std::string name;

    /**
     * @brief Long description of current room. Displayed when this
     * room is first visited.
     */
    std::string description;

    /**
     * @brief Short description of current room. Displayed every
     * time this room is visited, besides the first time.
     */
    std::string brief;

    /// Whether the room has been entered before.
    bool entered;

    /// Possible rooms to go to from here.
    Path path;

    /// List of actors within the room.
    std::list<Actor*> actors;

    /// List of items within the room.
    std::list<Item*> items;
};

/// Global pointer to current room.
extern Room* player_room;

#endif // ROOM_H
