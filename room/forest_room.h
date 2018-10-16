/**
 * @file forest_room.h
 * @brief Simple room to demonstrate enemies of a particular theme.
 */

#ifndef FOREST_ROOM_H
#define FOREST_ROOM_H

#include <room.h>

/// Room with a chance to spawn one of several themed enemies.
class Forest_Room : public Room
{
public:

    Forest_Room();

    Forest_Room* clone();

    void enter();
};

#endif // FOREST_ROOM_H
