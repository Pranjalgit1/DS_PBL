#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "spellchecker.h"
#include "heap.h"

void display_menu(void) {
    printf("\n========================================\n");
    printf("      ADVANCED DICTIONARY SYSTEM\n");
    printf("========================================\n");
    printf("1. Search for a word\n");
    printf("2. Insert a new word\n");
    printf("3. View top searched words\n");
    printf("4. Save dictionary\n");
    printf("5. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

int main(void) {
    printf("=== INITIALIZING DICTIONARY ===\n\n");
    // Create root node of Trie
    TrieNode *root = create_trienode();
    if (!root) {
        fprintf(stderr, "Error: Failed to create Trie root\n");
        return 1;
    }
    
    // Create heap and hashmap for tracking search frequency
    MaxHeap *search_heap = create_max_heap();
    HashMap *search_map = create_hash_map();
    if (!search_heap || !search_map) {
        fprintf(stderr, "Error: Failed to create search tracking structures\n");
        free_trie(root);
        return 1;
    }
    
    //  Loading dictionary from file
    const char *dict_file = "dictionary.txt";
    printf("Loading dictionary from '%s'...\n", dict_file);
    if (!load_dictionary(root, dict_file)) {
        printf("Warning: Could not load dictionary file. Starting with empty dictionary.\n");
    }
    // menu
    int choice;
    char word[MAX_LINE_LENGTH];
    char meaning[MAX_LINE_LENGTH];
    while (1) {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        getchar(); 
        switch (choice) {
            case 1: // Search for a word
                printf("\nEnter word to search: ");
                if (fgets(word, sizeof(word), stdin)) {
                    word[strcspn(word, "\n")] = '\0'; 
                    WordEntry *entry = search_word(root, word);
                    if (entry) {
                        print_word_meanings(word, entry);
                        // Track this search in the heap
                        track_search(search_heap, search_map, word);
                    } else {
                        printf("\n Word '%s' not found in dictionary\n", word);
                        printf("\n Running spell checker...\n");
                        run_spellchecker(word, dict_file);
                    }
                }
                break;
                
            case 2: // Insert a new word
                printf("\nEnter new word: ");
                if (fgets(word, sizeof(word), stdin)) {
                    word[strcspn(word, "\n")] = '\0';
                    printf("Enter meaning: ");
                    if (fgets(meaning, sizeof(meaning), stdin)) {
                        meaning[strcspn(meaning, "\n")] = '\0';
                        if (insert_word(root, word, meaning)) {
                            printf("\n Word '%s' inserted successfully!\n", word);
                        } else {
                            printf("\n Failed to insert word.\n");
                        }
                    }
                }
                break;
                
            case 3: // View top searched words
                printf("\nHow many top words do you want to see? (1-20): ");
                int n;
                if (scanf("%d", &n) == 1) {
                    getchar(); // consume newline
                    if (n < 1) n = 5;
                    if (n > 20) n = 20;
                    display_top_searched(search_heap, n);
                } else {
                    getchar();
                    printf("Invalid input! Showing top 5...\n");
                    display_top_searched(search_heap, 5);
                }
                break;
                
            case 4: // Save dictionary
                printf("\nSaving dictionary to '%s'...\n", dict_file);
                if (save_dictionary(root, dict_file)) {
                    printf("Dictionary saved successfully!\n");
                } else {
                    printf("Failed to save dictionary.\n");
                }
                break;
                
            case 5: // Exit
                printf("\nSaving dictionary before exit...\n");
                save_dictionary(root, dict_file);
                printf("\nCleaning up memory...\n");
                free_trie(root);
                free_max_heap(search_heap);
                free_hash_map(search_map);
                printf("Goodbye!\n\n");
                return 0;
            default:
                printf("invalid choice please select 1-5.\n");
        }
    }
    
    return 0;
}
