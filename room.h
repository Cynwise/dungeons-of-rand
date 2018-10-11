/**
 * @file room.h
 */

#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <string>

class Room;

/// Maps input strings to paths to other rooms.
typedef std::map<std::string, Room*> Path;

class Room
{
public:
	/// Add a path from this room.
	bool add_path(std::string entrance, Room* destination);
	
private:
	/// Possible rooms to go to from here.
	Path path;
	
	/// List of 
};

#endif // ROOM_H
