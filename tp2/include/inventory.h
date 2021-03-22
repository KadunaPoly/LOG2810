/**
 * File: inventory.h inventory.c
 * Desc: These files implements an inventory of the objects needed for this program
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/**
 * object_t - Defines what an object is
 * @name: String that contains the name of the object
 * @id: String that contains the id of the object
 * @type: String that contains the type of the object
 */
typedef struct {
	string name;
	string id;
	string type;
} object_t;

/**
 * search_t - Other name for the same thing
 *
 * Used when a user makes a search. We need the same three
 * attributes as an object.
 */
typedef object_t search_t;

/**
 * inventory_t - Array of objects
 * @size: Number of elements contained
 * @capacity: Number of elements that it can contain
 */
typedef vector<shared_ptr<object_t>> inventory_t;

/**
 * inventory_add_object() - Function that adds an object to an inventory
 * @inventory: Reference to the inventory to add the object
 * @object: Object to add to the inventory
 */
void inventory_add_object(inventory_t &inventory, object_t object);

/**
 * inventory_add_inventory() - Function that adds all the objects of an
 * inventory to another inventory
 * @inventory: Reference to the destinating inventory to add the objects
 * @objects: Reference of the source inventory that holds the objects to add
 */
void inventory_add_inventory(inventory_t &inventory, inventory_t objects);

/**
 * inventory_contains() - Function looks if a key is contained in the inventory
 * @inventory: Pointer to inventory to look for the key
 * @id: Id of the object to be found
 * return: returns the index to the object if found -1 if not found
 */
int inventory_contains(inventory_t inventory, const string id);

/**
 * inventory_contained_time() - Function looks how many times an object is
 * contained in the inventory
 * @inventory: Pointer to inventory to look for the object
 * @key: Id of the object to count the number of times its contained
 * return: returns the number of times the object with the id key is contained
 */
int inventory_contained_times(inventory_t inventory, const string id);

/**
 * inventory_remove() - Removes an object of an inventory
 * @inventory: Reference to the inventory to remove the object
 * @key: Id of the object to remove
 */
void inventory_remove(inventory_t &inventory, const string id);

/**
 * Print an object
 */
ostream& operator<<(ostream& os, const object_t& obj);

/**
 * Print an inventory
 */
ostream& operator<<(ostream& os, const inventory_t& v);

#endif
