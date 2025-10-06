#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stddef.h>

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
bool insert_word(TrieNode *root, const char *word, const char *meaning);
bool load_dictionary(TrieNode *root, const char *filename);
bool save_dictionary(TrieNode *root, const char *filename);
WordEntry *search_word(TrieNode *root, const char *word);
void print_word_meanings(const char *word, WordEntry *entry);

#endif
