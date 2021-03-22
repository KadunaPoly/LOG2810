#include <unordered_map>
#include <utility>

#include "parser.hpp"
#include "inventory.hpp"
#include "trie.hpp"

using namespace std;

int
main(void)
{
	Trie trie_name;
	Trie trie_id;
	Trie trie_type;

	if(!parse_file("../inventaire.txt", trie_name, trie_id, trie_type))
		exit(1);

	unordered_map<char, shared_ptr<state_t>> childs;

	// state_t *state = trie_search(trie_name, "avion");

	// printf("%s\n", state->inventory->objects[0]->id);
	// inventory_remove(state->inventory, "B16A49");
	// printf("%s\n", state->inventory->objects[0]->id);

	// printf("%s\n", trie_search(trie_id, "B16A49")->inventory[0].objects[0]->id);
	// trie_remove(trie_id, "B16A49", "B16A49");
	// printf("%p\n", trie_search(trie_id, "B16A49"));

	// printf("%s\n", trie_search(trie_name, "avion")->inventory->objects[0]->id);

	return 0;
}
