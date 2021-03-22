#include "trie.h"

#include <stdio.h>

int
main()
{
	trie_t *trie = trie_alloc();
	// trie_search(trie, "hel");
	// wordlist_t *wordlist = trie_search(trie, "he")->wordlist;
	// for(size_t i = 0; i < wordlist->size; ++i)
	// 	printf("%s\n", wordlist->words[i]);
	// printf("%s\n", trie_search(trie, "hello"));
	// printf("%s\n", trie_search(trie, "heslo"));
	// printf("%s\n", trie_search(trie, "sello"));
	// printf("%s\n", trie_search(trie, "2ello"));
	// printf("%s\n", trie_search(trie, "3ello"));

	// wordlist_t *wordlist = wordlist_alloc();
	// char *str = calloc(1, sizeof(char *));
	// wordlist_add(wordlist, str);

	// wordlist_free(wordlist);
	trie_free(trie);
	return 0;
}
