#include "parser.h"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

bool
parse_file(const string inventory_file, Trie &trie_name, Trie &trie_id, Trie &trie_type)
{
	string line;
	ifstream in;

	in.open(inventory_file);

	if(!in.is_open())
		return false;

	while(getline(in, line)) {
		if(line.length() == 1)
			break;

		stringstream read;
		string name;
		string id;
		string type;

		read << line;

		read >> name;
		read.ignore();

		read >> id;
		read.ignore();

		read >> type;
		read.ignore();


		trie_name.insert(name, object_t{.name = name, .id = id, .type = type});
		trie_id.insert(id, object_t{.name = name, .id = id, .type = type});
		trie_type.insert(type, object_t{.name = name, .id = id, .type = type});
	}

	in.close();

	return true;
}

void
parse_search(search_t &search)
{
	search.name = "";
	search.id = "";
	search.type = "";

	cout << "Filtrer par nom : ";
	readword(search.name);

	cout << "Filtrer par id : ";
	readword(search.id);

	cout << "Filtrer par type : ";
	readword(search.type);
}

void
readword(string &word)
{
	word = "";

	string line;
	getline(cin, line);
	stringstream ss(line);
	ss >> word;
}
