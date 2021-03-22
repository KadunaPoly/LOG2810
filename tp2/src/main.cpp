#include "parser.h"
#include "inventory.h"
#include "trie.h"

#include <iostream>
#include <sstream>

static Trie trie_name;  // Trie that recognizes the names
static Trie trie_id;    // Trie that recognizes the ids
static Trie trie_type;  // Trie that recognizes the types

static inventory_t basket; // basket of the user

static int weight = 0; // weight of the basket


static int
menu()
{

	int choice;
        char selection;

	do{
		printf(" Selectionnez parmi les options suivantes\n"
		       " ----------------------------------------------\n"
		       " - Initialiser le programme (a)\n"
		       " - Chercher un objet (b)\n"
		       " - Ajouter au panier (c)\n"
		       " - Voir panier (d)\n"
		       " - Vider le panier (e)\n"
		       " - Passer une commande (f)\n"
		       " - Quitter (q)\n : ");

		cin >> selection;

		switch (selection) {

		case 'a':
			choice = 0;
			break;
		case 'b':
			choice = 1;
			break;
		case 'c':
			choice = 2;
			break;
		case 'd':
			choice = 3;
			break;
		case 'e':
			choice = 4;
			break;
		case 'f':
			choice = 5;
			break;
		case 'q':
			choice = 6;
			break;
		default:
			printf("\nInvalide : Les options possibles sont: {a, b, c, d, e, f, q}\n\n");
			choice = -1;
		}


	} while(choice == -1);

	printf("\n");

	return choice;
}

/** initialiserProgramme() - Function that initializes the three automatons */
static void
initialiserProgramme()
{
	trie_name.clear();
	trie_id.clear();
	trie_type.clear();


	trie_name = Trie();
	trie_id = Trie();
	trie_type = Trie();

	string inventory_path;

	cin.ignore();
	string answer;
	do {
		cout << "Entrez le nom du fichier : ";
		readword(inventory_path);
		cout << endl;

		answer = "n";

		if(!parse_file(inventory_path, trie_name, trie_id, trie_type)) {
			cout << "Le fichier n'a pas pu etre trouve reessaye ? (o) : ";
			readword(answer);
		}

	} while(answer[0] == 'o');
}

/** search_object() - Main search function
 * @search: Object containing the three filters
 *
 * This function searches objects on the three automaton
 * with the filters contained in %search. It than filters
 * the object not corresponding to the three filters
 */
static void
search_object(const search_t &search)
{
	shared_ptr<state_t> final_state_name;
	shared_ptr<state_t> final_state_id;
	shared_ptr<state_t> final_state_type;

        inventory_t completions_name;
	inventory_t completions_id;
	inventory_t completions_type;

	inventory_t merged;

	int count = 0;
	bool found = false;

	if(search.name.length() == 0 && search.id.length() == 0 && search.type.length() == 0) {

		final_state_name = trie_name.search("");
		completions_name = final_state_name->inventory;

	} else{
		if(search.name.length() > 0) {
			++count;

			final_state_name = trie_name.search(search.name);

			if(final_state_name) {
				completions_name = final_state_name->inventory;
				inventory_add_inventory(merged, completions_name);
			} else {
				goto notfound;
			}
		}
		if (search.id.length() > 0) {
			++count;

			final_state_id = trie_id.search(search.id);
			if(final_state_id) {
				completions_id = final_state_id->inventory;
				inventory_add_inventory(merged, completions_id);
			} else {
				goto notfound;
			}
		}
		if(search.type.length() > 0) {
			++count;

			final_state_type = trie_type.search(search.type);

			if(final_state_type) {
				completions_type = final_state_type->inventory;
				inventory_add_inventory(merged, completions_type);
			} else {
				goto notfound;
			}
		}
	}

	if(completions_type.size() > 0) {
		for(size_t i = 0, isfirst = 0; i < completions_type.size(); ++i) {
			if(inventory_contained_times(merged, completions_type[i]->id) == count) {
				if(isfirst == 0)
					cout << "Objets correspondants a la recherche : " << endl;
				++isfirst;
				cout << *completions_type[i] << endl;
				found = true;
			}

		}
	}else if(completions_id.size() > 0) {
		for(size_t i = 0, isfirst = 0; i < completions_id.size(); ++i)
			if(inventory_contained_times(merged, completions_id[i]->id) == count) {
				if(isfirst == 0)
					cout << "Objets correspondants a la recherche : " << endl;
				++isfirst;
				cout << *completions_id[i] << endl;
				found = true;
			}

	} else if(completions_name.size() > 0){
		for(size_t i = 0, isfirst = 0; i < completions_name.size(); ++i)
			if(inventory_contained_times(merged, completions_name[i]->id) == count) {
				if(isfirst == 0)
					cout << "Objets correspondants a la recherche : " << endl;
				++isfirst;
				cout << *completions_name[i] << endl;
				found = true;
			}

	}

notfound:
	if(!found)
		cout << "Aucun objet correspond a la recherche" << endl;

	cout << endl;
}

static void
chercherObjet()
{

	if(trie_name.start->inventory.size() == 0) {
		printf("Veuillez initialiser le programme\n\n");
		return;
	}

	string answer;

	static search_t	search;

	cin.ignore();
	do {
		parse_search(search);
		cout << endl;
		search_object(search);

		cout << "Faire une autre recherche ? (o) : ";

		readword(answer);

	} while(answer[0] == 'o');

}

static void
afficherPanier()
{
	if(basket.size() == 0) {
		cout << "Le panier est vide\n" << endl;
		return;
	}

	cout << "Etat du panier: \n" << basket << endl;
	cout << "Poids total: " << weight << "\n" << endl;
}

static void
ajouterPanier(string object_id)
{
	shared_ptr<state_t> state = trie_id.search(object_id);

	if(state == nullptr || !state->terminal) {
		cout << "L'objet na pas pu etre trouve\n" << endl;
		return;
	}

	object_t object = *state->inventory[inventory_contains(state->inventory, object_id)];

	string object_name(object.name);
	string object_type(object.type);

	switch(object_type[0]) {
	case 'A':
		weight += 1;
		break;
	case 'B':
		weight += 3;
		break;
	case 'C':
		weight += 5;
		break;
	}

	inventory_add_object(basket,
			     (object_t ){.name = object_name,
					     .id = object_id,
					     .type = object_type});


	cout << "L'objet : [" << object
	     << "] a ete ajoute au panier\n" << endl;

	afficherPanier();

	trie_id.remove(object_id, object_id);
	trie_name.remove(object_name, object_id);
	trie_type.remove(object_type, object_id);

}

static void
ajouterPanier()
{
	if(trie_name.start->inventory.size() == 0) {
		printf("Veuillez initialiser le programme\n\n");
		return;
	}

	string answer = "n";
	cin.ignore();
	do {
		string object_id = "";

		printf("Entrez le code identifiant : ");
		readword(object_id);
		printf("\n");

		ajouterPanier(object_id);

		cout << "Ajouter un autre object? (o) : ";
		readword(answer);
	} while(answer[0] == 'o');
}

static void
retirerPanier()
{
	if(trie_name.start->inventory.size() == 0) {
		cout << "Veuillez initialiser le programme\n" << endl;
		return;
	}

	if(basket.size() == 0) {
		cout << "Le panier est vide\n" << endl;
		return;
	}

	cout << "Le panier suivant sera vide: \n";
	afficherPanier();

	cin.ignore();
	string answer;
	cout << "Continuer (o)? : ";
	readword(answer);

	if(answer[0] != 'o') {
		cout << "Retrait annule\n" << endl;
		return;
	}

	for(size_t i = 0; i < basket.size(); ++i) {
		trie_id.insert(basket[i]->id, *basket[i]);
		trie_name.insert(basket[i]->name, *basket[i]);
		trie_type.insert(basket[i]->type, *basket[i]);
	}

	weight = 0;
	basket.clear();

	cout << "Le panier a ete vide avec succes\n" << endl;
}

static void
passerCommande()
{
	if(basket.size() == 0) {
		cout << "Le panier est vide\n" << endl;
		return;
	}

	if(weight > 25) {
		cout << "Commande trop lourde : " << weight << "kg > 25kg\n" << endl;
		return;
	}

	cout << "La commande suivante va etre passe: \n";
	afficherPanier();

	cin.ignore();
	string answer;
	cout << "Continuer (o)? : ";
	readword(answer);

	if(answer[0] == 'o') {
		weight = 0;
		basket.clear();
		cout << "La commande a ete passe avec succes\n" << endl;
	} else {
		cout << "Commande annulee\n" << endl;
	}
}

static void
quit()
{
	exit(0);
}


static void (*actions[7])(void) = {
	initialiserProgramme,
	chercherObjet,
	ajouterPanier,
	afficherPanier,
	retirerPanier,
	passerCommande,
	quit
};

int
main(void)
{
	for(;;) {
		int action = menu();

		(*actions[action]) ();
	}
	return 0;
}
