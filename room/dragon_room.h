/**
 * @file dragon_room.h
 * @brief Simple room to demonstrate a room with enemies in it.
 */

#ifndef DRAGON_ROOM_H
#define DRAGON_ROOM_H

#include <room.h>

/// Room that spawns a Dragon.
class Dragon_Room : public Room
{
public:

    Dragon_Room();

    Dragon_Room* clone();

    void enter();
};

#endif // DRAGON_ROOM_H
