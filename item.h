/**
 * @file item.h
 */

#ifndef ITEM_H
#define ITEM_H

class Actor;

/// Generic base class for usable items.
class Item
{
public:
	Item();
	
	/// Apply the item's effects to actor.
	virtual void use(Actor& user) = 0;
};

#endif // ITEM_H
