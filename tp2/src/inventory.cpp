#include "inventory.h"

#include <memory>
#include <iostream>

void
inventory_add_object(inventory_t &inventory, object_t object)
{
	inventory.push_back(make_shared<object_t>());


	inventory[inventory.size() - 1]->name = object.name;
	inventory[inventory.size() - 1]->id = object.id;
	inventory[inventory.size() - 1]->type = object.type;
}

void
inventory_add_inventory(inventory_t &inventory, inventory_t objects)
{
	for(size_t i = 0; i < objects.size(); ++i) {
		inventory_add_object(inventory, *objects[i]);
	}
}

int
inventory_contained_times(inventory_t inventory, const string id)
{
	int times = 0;
	for(size_t i = 0; i < inventory.size(); ++i) {
		if(id.compare(inventory[i]->id) == 0)
			++times;
	}

	return times;
}

int
inventory_contains(inventory_t inventory, const string id)
{
	for(size_t i = 0; i < inventory.size(); ++i) {

		if(id.compare(inventory[i]->id) == 0)
			return i;

	}

	return -1;
}

void
inventory_remove(inventory_t &inventory, const string id)
{
	int index = inventory_contains(inventory, id);

	// for(shared_ptr<object_t> obj : inventory)
	// cout << obj->id << endl;

	if(index == -1)
		return;

	inventory[index] = nullptr;

	if(inventory.size() > 1) {
		inventory[index] = inventory[inventory.size() - 1];
		inventory.pop_back();
	} else {
		inventory.pop_back();
	}

	// for(shared_ptr<object_t> obj : inventory)
	// cout << obj->id << endl;
}

ostream&
operator<<(ostream& os, const object_t& obj)
{
	os << obj.name << " " << obj.id << " " << obj.type;

	return os;
}

ostream&
operator<<(ostream& os, const inventory_t& v)
{
	for(size_t i = 0; i < v.size(); ++i) {
		os << "[" << *v[i] << "]" << endl;
	}

	return os;
}
