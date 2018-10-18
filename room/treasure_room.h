/**
 * @file treasure_room.h
 * @brief room to be used when items are implemented.
 */

#ifndef TREASURE_ROOM_H
#define TREASURE_ROOM_H

#include <room.h>

/// Room that rewards player with an item.
class Treasure_Room : public Room
{
public:

    Treasure_Room();

    Treasure_Room* clone();

    void enter();
};

#endif // TREASURE_ROOM_H
