/**
 * @file rat_room.h
 * @brief Simple room to demonstrate a room with enemies in it.
 */

#ifndef RAT_ROOM_H
#define RAT_ROOM_H

#include <room.h>

/// Room with a spawned Rat.
class Rat_Room : public Room
{
public:

    Rat_Room();

    Rat_Room* clone();

    void enter();
};

#endif // RAT_ROOM_H
