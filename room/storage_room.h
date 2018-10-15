/**
 * @file storage_room.h
 * @brief Simple room to demonstrate a room with a chance for different enemies in it.
 */

#ifndef STORAGE_ROOM_H
#define STORAGE_ROOM_H

#include <room.h>

class Storage_Room : public Room
{
public:

    Storage_Room();

    Storage_Room* clone();

    void enter();
};

#endif // SORAGE_ROOM_H
