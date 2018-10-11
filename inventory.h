/**
 * @file inventory.h
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <list>

class Item;

class Inventory
{
public:
	/// Insert an item into the inventory.
	void insert(Item& item);
	
private:

	std::list<Item> contents;
};

#endif // INVENTORY_H
