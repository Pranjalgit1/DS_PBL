#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdbool.h>
#include <stddef.h>
#include "heap.h"

#define ALPHABET_SIZE 26
#define MAX_LINE_LENGTH 1024
#define MAX_MEANINGS 10
typedef struct MeaningNode {
    char *meaning;
    struct MeaningNode *next;
} MeaningNode;
typedef struct WordEntry {
    MeaningNode *meanings_head;
    int search_count;
} WordEntry;
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    WordEntry *word_entry;
    bool is_end_of_word;
} TrieNode;

TrieNode *create_trienode(void);
void free_trie(TrieNode *root);
bool insert_word(TrieNode *root,  char *word,  char *meaning);
bool delete_word(TrieNode *root,  char *word);
bool load_dictionary(TrieNode *root,  char *filename);
bool save_dictionary(TrieNode *root,  char *filename);
WordEntry *search_word(TrieNode *root,  char *word);
void print_word_meanings( char *word, WordEntry *entry);
void track_search(MaxHeap* heap, HashMap* map, const char* word);
void display_top_searched(MaxHeap* heap, int n);

#endif
