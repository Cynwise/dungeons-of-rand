/**
 * @file forest.h
 * @brief Simple room to demonstrate enemies of a particular theme.
 */

#ifndef FOREST_H
#define FOREST_H

#include <room.h>

/// Room with a chance to spawn one of several themed enemies.
class Forest : public Room
{
public:

    Forest();

    Forest* clone();

    void enter();
};

#endif // FOREST_H
