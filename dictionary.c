#include "dictionary.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

 
static void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

 MeaningNode *create_meaning_node( char *meaning) {
    MeaningNode *node = (MeaningNode *)malloc(sizeof(MeaningNode));
    if (!node) return NULL;
    node->meaning = strdup(meaning);
    if (!node->meaning) {
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

bool add_meaning(WordEntry *entry, char *meaning) {
    if (!entry || !meaning) return false;
    MeaningNode *new_node = create_meaning_node(meaning);
    if (!new_node) return false;
    // Add to end of list
    if (!entry->meanings_head) {
        entry->meanings_head = new_node;
    } else {
        MeaningNode *curr = entry->meanings_head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
    return true;
}

 void free_meanings(MeaningNode *head) {
    while (head) {
        MeaningNode *temp = head;
        head = head->next;
        free(temp->meaning);
        free(temp);
    }
}
 
char *trim_whitespace(char *str) {
    // Trim leading
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    // trim trailng
    char *end = str + strlen(str) - 1;
    while (end>str &&isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    
    return str;
}

TrieNode *create_trienode(void) {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (!node) return NULL;
    node->is_end_of_word = false;
    node->word_entry = NULL;
    for (int i =0; i <ALPHABET_SIZE;i++) {
        node->children[i] = NULL;
    }
    return node;
}

void free_trie(TrieNode *root) {
    if (!root) return;
    // Recursively free all childrens
    for (int i =0; i <ALPHABET_SIZE;i++) {
        if (root->children[i]) {
            free_trie(root->children[i]);
        }
    }
    if (root->word_entry) {
        free_meanings(root->word_entry->meanings_head);
        free(root->word_entry);
    }
    free(root);
}

bool insert_word(TrieNode *root, char *word, char *meaning) {
    if (!root || !word || !meaning) return false;
    char word_lower[MAX_LINE_LENGTH];
    strncpy(word_lower, word, MAX_LINE_LENGTH - 1);
    word_lower[MAX_LINE_LENGTH - 1]= '\0';
    to_lowercase(word_lower);
    
    TrieNode *curr = root;
    for (int i =0;word_lower[i] !='\0';i++) {
        if (!isalpha((unsigned char)word_lower[i])) { 
            continue;
        }
        int index= word_lower[i] - 'a';
        if (index <0 || index>=ALPHABET_SIZE) continue;
        
        if (!curr->children[index]) {
            curr->children[index] = create_trienode();
            if (!curr->children[index]) return false;
        }
        curr = curr->children[index];
    }
    curr->is_end_of_word = true;
    if (!curr->word_entry) {
        curr->word_entry = (WordEntry *)malloc(sizeof(WordEntry));
        if (!curr->word_entry) return false;
        curr->word_entry->meanings_head = NULL;
        curr->word_entry->search_count = 0;
    }
    return add_meaning(curr->word_entry, meaning);
}

WordEntry *search_word(TrieNode *root, char *word) {
    if (!root || !word) return NULL;
    char word_lower[MAX_LINE_LENGTH];
    strncpy(word_lower, word, MAX_LINE_LENGTH - 1);
    word_lower[MAX_LINE_LENGTH - 1] = '\0';
    to_lowercase(word_lower);
    TrieNode *curr = root;
    for (int i= 0;word_lower[i]!='\0';i++) {
        if (!isalpha((unsigned char)word_lower[i])) continue;
        int index = word_lower[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) return NULL;
        if (!curr->children[index]) return NULL;
        curr = curr->children[index];
    }
    if (curr->is_end_of_word && curr->word_entry) {
        curr->word_entry->search_count++;
        return curr->word_entry;
    }
    return NULL;
}

void print_word_meanings( char *word, WordEntry *entry) {
    if (!entry) return;
    printf("\n--- Word: %s ---\n", word);
    printf("Search count: %d\n", entry->search_count);
    printf("Meanings:\n");
    int count = 1;
    MeaningNode *curr = entry->meanings_head;
    while (curr) {
        printf("  %d. %s\n", count++, curr->meaning);
        curr = curr->next;
    }
    printf("\n");
}

bool load_dictionary(TrieNode *root, char *filename) {
    if (!root || !filename) return false;
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error cannot open file '%s'\n", filename);
        return false;
    }
    char line[MAX_LINE_LENGTH];
    int line_num = 0;
    int words_loaded = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line_num++;
        line[strcspn(line, "\r\n")] = '\0';
        // skip empty lines and comments
        char *trimmed = trim_whitespace(line);
        if (strlen(trimmed) == 0 || trimmed[0] == '#') continue;
        // Parse line= word|meaning1;meaning2;meaning3.........so on
        char *pipe_pos = strchr(trimmed, '|');
        if (!pipe_pos) {
            fprintf(stderr, " invalid format at line %d (no '|')\n", line_num);
            continue;
        }
        // Extract word
        *pipe_pos = '\0';
        char *word = trim_whitespace(trimmed);
        char *meanings_str = trim_whitespace(pipe_pos + 1);
        if (strlen(word) == 0) {
            fprintf(stderr, "Empty word at line %d\n", line_num);
            continue;
        }
        char *meaning_token = strtok(meanings_str, ";");
        bool word_inserted = false;
        while (meaning_token) {
            char *meaning = trim_whitespace(meaning_token);
            if (strlen(meaning) > 0) {
                if (insert_word(root, word, meaning)) {
                    word_inserted = true;
                } else {
                    fprintf(stderr, "Failed to insert meaning at line %d\n", line_num);
                }
            }
            meaning_token = strtok(NULL, ";");
        }
        if (word_inserted) words_loaded++;
    }
    fclose(file);
    printf("Dictionary loaded: %d words from '%s'\n", words_loaded, filename);
    return true;
}


static void save_trie_helper(TrieNode *node, char *prefix, int level, FILE *file) {
    if (!node) return;
    if (node->is_end_of_word && node->word_entry) {
        prefix[level] = '\0';
        fprintf(file, "%s|", prefix);
        MeaningNode *curr = node->word_entry->meanings_head;
        bool first = true;
        while (curr) {
            if (!first) fprintf(file, ";");
            fprintf(file, "%s", curr->meaning);
            curr = curr->next;
            first = false;
        }
        fprintf(file, "\n");
    }
    // Recursion for all children
    for (int i=0; i< ALPHABET_SIZE;i++) {
        if (node->children[i]) {
            prefix[level] = 'a' + i;
            save_trie_helper(node->children[i], prefix, level + 1, file);
        }
    }
}

bool save_dictionary(TrieNode *root, char *filename) {
    if (!root || !filename) return false;
    FILE *file= fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Erro Cannot create file '%s'\n", filename);
        return false;
    }
    char prefix[MAX_LINE_LENGTH];
    save_trie_helper(root, prefix, 0, file);
    fclose(file);
    printf("Dictionary saved to '%s'\n", filename);
    return true;
}

void track_search(MaxHeap* heap, HashMap* map, const char* word) {
    if (!heap || !map || !word) return;
    increase_freq(heap, map, word, 1);
}

void display_top_searched(MaxHeap* heap, int n) {
    if (!heap) return;
    get_top_searched_words(heap, n);
}
