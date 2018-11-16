/**
 * @file room.h
 * @brief Generic base class for all environments. Also declare
 * global pointer to current room.
 */

#ifndef ROOM_H
#define ROOM_H

#include <list>
#include <map>
#include <memory>
#include <string>

class Actor;
class Item;
class Room;
class Room_Module;

/// Maps input strings to paths to other rooms.
typedef std::map<std::string, Room*> Path;

/// Generic base class for all environments.
class Room
{
public:

    Room();

    virtual ~Room();

    /// Assignment operator.
    Room& operator=(const Room& other);

    /// Create a room of a given type.
    Room(const std::string& type);

    /**
     * @brief Add a one-way path to another room.
     *
     * @param to String describing the direction.
     * @param dest Destination room.
     */
    void add_one_way(const std::string& to, Room& dest);

    /**
     * @brief Add a two-way path to another room.
     *
     * @param to String describing the direction to go.
     * @param back String describing the return direction.
     * @param dest Destination room.
     */
    void add_two_way(
        const std::string& to,
        const std::string& back,
        Room& dest);

    /// Call to enter this room.
    virtual void enter();

    /// Go to different room by path.
    virtual void go(const std::string& key);

    /// Print a full overview of the room and its contents.
    virtual void print_full();

    /// Print a short overview of the room and its contents.
    virtual void print_brief();

    /// Print all Actors and Items in the room.
    virtual void print_contents();

    /// Add an Actor to this room.
    virtual void add_actor(std::unique_ptr<Actor> actor);

    /// Find an Actor by name.
    virtual Actor* find_actor(const std::string& name);

    /// Remove an Actor from this room.
    virtual std::unique_ptr<Actor> remove_actor(Actor* actor);

    /// Find an Item by name.
    virtual Item* find_item(const std::string& name);

    /// Add an Item to this room.
    virtual void add_item(std::unique_ptr<Item> item);

    /// Remove an Item from this room.
    virtual std::unique_ptr<Item> remove_item(Item* item);

    /// Return whether there are any hostiles in this room.
    virtual bool is_safe() const;

    // Getters/setters.
    std::string get_name();
    void set_name(const std::string& s);
    std::string get_description();
    void set_description(const std::string& s);
    std::string get_brief();
    void set_brief(const std::string& s);

protected:

    /// Let game loop access Actors.
    friend int game_loop();
    friend void player_turn();

    /// Room type identifier.
    std::string type;

    /// Name of current room.
    std::string name;

    /**
     * @brief Short description of current room. Displayed every
     * time this room is visited, besides the first time.
     */
    std::string brief;

    /**
     * @brief Long description of current room. Displayed when this
     * room is first visited.
     */
    std::string description;

    /// Whether the room has been entered before.
    bool entered;

    /// Possible rooms to go to from here.
    Path path;

    /// List of actors within the room.
    std::list<std::unique_ptr<Actor>> actors;

    /// List of items within the room.
    std::list<std::unique_ptr<Item>> items;
};

/// Global pointer to current room.
extern Room* player_room;

#endif // ROOM_H
