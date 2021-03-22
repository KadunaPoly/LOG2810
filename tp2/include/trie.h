/**
 * @File: trie.h trie.cpp
 * @Desc: implementation of the automaton that recognizes words from the text file
 */

#ifndef TRIE_H
#define TRIE_H

#include "inventory.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

/**
 * state_t - State used as node for the trie graph
 * @transition: Character to check to transition from one state to another
 * @terminal: boolean that tells if the state is a final state
 * @nterminals: counter to know how many words finish in that state
 * @childs: Array of nodes that can be reached from current state
 * @inventory: Inventory of objects contained in the current state
 */
typedef struct state_t state_t;
struct state_t {
	char transition;
	bool terminal;
	int nterminals;
	vector<shared_ptr<state_t>> childs;
	inventory_t inventory;
};

/**
 * Trie - Main class
 *
 * The trie is the main data structure used to implement the automaton
 */
class Trie {

private:

	bool insert(shared_ptr<state_t> state, string input, size_t index, object_t object);
	shared_ptr<state_t> state_search(shared_ptr<state_t> state, const string key);
	void delete_child(shared_ptr<state_t> parent, size_t child_index, const string id);
	void state_remove(shared_ptr<state_t> state, int pos, string key, const string id);
public:
	shared_ptr<state_t> start;

	/**
	 * Trie() - Default constructor
	 */
	Trie();

	/**
	 * ~Trie() - Default destructor
	 */
	~Trie();

	/**
	 * insert() - Recursive function that inserts a word to the trie
	 * and its object
	 * @input: String to insert
	 * @object: Corresponding object to insert
	 *
	 * This function is used to create all the states needed to recognize
	 * the string and inserts the object to each state traversed.
	 */
	void insert(string input, object_t object);

	/** remove() - Function used to remove an object of the automatom
	 * @key: Word from which we remove the object
	 * @id: String that tells the exact object to remove
	 *
	 * This function first remove the corresponding object of the final
	 * state. Then it removes the object from all the traversed states.
	 */
	void remove(string key, const string id);

	/** clear() - Makes the trie empty */
	void clear();

	/**
	 * search() - Used to find a state from a string
	 * @key: The string used to get the state
	 * return: The final state reached by the string if found %nullptr if not
	 *
	 * This function take a string and inputs it to the automaton and returns
	 * the final state reached if found. The final state returned, contains
	 * all the objects of the complete words that the state can reach.
	 * Therefore given an empty string the function returns the start state
	 * that contains the full inventory
	 */
	shared_ptr<state_t> search(const string key);

};

#endif
