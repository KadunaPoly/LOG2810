/**
 * File: parse.h parser.cpp
 * Desc: These files contain a set of functions used
 * to parse files or command line inputs
 */

#ifndef PARSER_H
#define PARSER_H

#include "inventory.h"
#include "trie.h"

/**
 * parse_file() - Function that parses a file and builds three automatons
 * @inventory_file: string that contains the path of the file containing
 * the inventory
 * @trie_name: Reference to the automaton that will be build with the
 * names of the objects
 * @trie_id: Reference to the automaton that will build with the ids
 * of the objects
 * @trie_type: Reference to the automaton that will build with the types
 * of the objects
 * return: returns true on succesful parsing else it returns false
 *
 * We want to build three automatons for each caracteristics of an object_t
 * (name, id, type). We need three so we can filter the objects by name, id
 * and type.
 */
bool parse_file(const string inventory_file,
		Trie &trie_name,
		Trie &trie_id,
		Trie &trie_type);

/**
 * parse_search() - Function that parses the input of the command line into struct search
 * @search: Reference to the search struct to be parsed
 *
 * This is the function used to receive the filters from the user and puts it in
 * the search struct.
 */
void parse_search(search_t &search);

/**
 * readword() - Function used read a word into a string
 * @line: Reference to the line that will contain the user input
 */
void readword(string &word);
#endif
