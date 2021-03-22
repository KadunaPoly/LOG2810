#include "trie.h"

using namespace std;

Trie::Trie()
	: start(make_shared<state_t>((state_t)
				     {.transition = ' ', .terminal = false, .nterminals = 0})){}

Trie::~Trie()
{}

bool
Trie::insert(shared_ptr<state_t> state, string input, size_t index, object_t object)
{
	if(index == input.size()) {
		if(inventory_contains(state->inventory, object.id) == -1)
			inventory_add_object(state->inventory, object);

		state->terminal = true;
		++state->nterminals;
		return true;
	}

	for(size_t i = 0; i < state->childs.size() + 1; ++i) {
		if(i < state->childs.size() && state->childs[i]->transition == input[index]) {

			if (insert(state->childs[i], input, index + 1, object)) {
				if(inventory_contains(state->inventory, object.id) == -1)
					inventory_add_object(state->inventory, object);
				return true;
			}

			return false;

		} else if(i >= state->childs.size()) {

			state->childs.push_back(make_shared<state_t>());
			state->childs[i]->transition = input[index];
			state->childs[i]->terminal = false;
			state->childs[i]->nterminals = 0;


			insert(state->childs[i], input, index + 1, object);

			if(inventory_contains(state->inventory, object.id) == -1)
				inventory_add_object(state->inventory, object);

			return true;
		}

	}

	return false;
}

void
Trie::insert(string input, object_t object)
{
	insert(start, input, 0, object);
}

shared_ptr<state_t>
Trie::state_search(shared_ptr<state_t> state, const string key)
{
	bool found = false;
	shared_ptr<state_t> itr = state;
	for(size_t i = 0; i < key.size(); ++i) {
		found = false;
		for(size_t j = 0; j < itr->childs.size(); ++j) {
			if(itr->childs[j]->transition == key[i]) {
				itr = itr->childs[j];
				found = true;
				break;
			}
		}

		if(!found)
			break;
	}

	if(found)
		return itr;
	else
		return nullptr;
}

shared_ptr<state_t>
Trie::search(const string key)
{
	if(key.length() == 0)
		return start;

	return state_search(start, key);
}

void
Trie::delete_child(shared_ptr<state_t> parent, size_t child_index, const string id)
{
	shared_ptr<state_t> child = parent->childs[child_index];
	int contained = inventory_contains(child->inventory, id);

	if(contained == -1)
		return;

	if(child->inventory.size() <= 1 && child->childs.size() == 0) {

		parent->childs[child_index] = parent->childs[parent->childs.size() - 1];
		parent->childs.pop_back();

	} else {
		inventory_remove(child->inventory, id);

		if(child->nterminals == 1)
			child->terminal = false;

		if(child->nterminals > 0)
			--child->nterminals;
	}
}

void
Trie::state_remove(shared_ptr<state_t> state, int pos, string key, const string id)
{
	shared_ptr<state_t> parent = state;
	shared_ptr<state_t> current = state;

	if(!state_search(state, key))
		return;

	for(size_t j = 0; j < state->childs.size(); ++j) {
		if(current->childs[j]->transition == key[pos]) {
			current = current->childs[j];

			state_remove(current, pos, key.substr(pos + 1), id);
			delete_child(parent, j, id);
			return;
		}
	}


}

void
Trie::remove(string key, const string id)
{
	state_remove(start, 0, key, id);

	inventory_remove(start->inventory, id);
}

void
Trie::clear()
{
	start->childs.clear();
}
