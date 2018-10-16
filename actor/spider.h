/**
 * @file Spider.h
 * @brief Simple animal enemy class.
 */

#ifndef SPIDER_H
#define SPIDER_H

#include <actor.h>

/// Simple enemy class.
class Spider : public Actor
{
public:

    Spider();

    Spider* clone();
};

#endif // SPIDER_H
