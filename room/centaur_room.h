/**
 * @file barbarian_room.h
 * @brief Simple room to demonstrate a room with enemies in it.
 */

#ifndef CENTAUR_ROOM_H
#define CENTAUR_ROOM_H

#include <room.h>

/// Room that spawns a Centaur.
class Centaur_Room : public Room
{
public:

    Centaur_Room();

    Centaur_Room* clone();

    void enter();
};

#endif // CENTAUR_ROOM_H
