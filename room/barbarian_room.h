/**
 * @file barbarian_room.h
 * @brief Simple room to demonstrate a room with enemies in it.
 */

#ifndef BARBARIAN_ROOM_H
#define BARBARIAN_ROOM_H

#include <room.h>

class Barbarian_Room : public Room
{
public:

    Barbarian_Room();

    Barbarian_Room* clone();

    void enter();
};

#endif // BARBARIAN_ROOM_H
