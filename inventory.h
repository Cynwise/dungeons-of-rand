/**
 * @file inventory.h
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <list>
#include <string>
#include <utility>

class Item;

class Inventory
{
public:

	/// Initialize an empty inventory.
	Inventory();
	
	/// Delete all contents.
	~Inventory();

	/// Insert an item into the inventory.
	void insert(Item& item);
	
	/// Finds an item by name.
	Item* find_by_name(const std::string& key) const;
	
private:

	std::list<Item*> contents;
};

#endif // INVENTORY_H
