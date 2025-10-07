#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "spellchecker.h"

void display_menu(void) {
    printf("\n========================================\n");
    printf("      ADVANCED DICTIONARY SYSTEM\n");
    printf("========================================\n");
    printf("1. Search for a word\n");
    printf("2. Insert a new word\n");
    printf("3. Save dictionary\n");
    printf("4. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

int main(void) {
    printf("=== INITIALIZING DICTIONARY ===\n\n");
    
    // Step 1: Create root node of Trie
    TrieNode *root = create_trienode();
    if (!root) {
        fprintf(stderr, "Error: Failed to create Trie root\n");
        return 1;
    }
    
    // Step 2: Load dictionary from file
    const char *dict_file = "dictionary.txt";
    printf("Loading dictionary from '%s'...\n", dict_file);
    if (!load_dictionary(root, dict_file)) {
        printf("Warning: Could not load dictionary file. Starting with empty dictionary.\n");
    }
    
    // Step 3: Interactive menu
    int choice;
    char word[MAX_LINE_LENGTH];
    char meaning[MAX_LINE_LENGTH];
    
    while (1) {
        display_menu();
        
        if (scanf("%d", &choice) != 1) {
            // Clear invalid input
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        getchar(); // Consume newline
        
        switch (choice) {
            case 1: // Search for a word
                printf("\nEnter word to search: ");
                if (fgets(word, sizeof(word), stdin)) {
                    word[strcspn(word, "\n")] = '\0'; // Remove newline
                    
                    WordEntry *entry = search_word(root, word);
                    if (entry) {
                        print_word_meanings(word, entry);
                    } else {
                        printf("\n❌ Word '%s' not found in dictionary.\n", word);
                        printf("\n🔍 Running spell checker...\n");
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
                            printf("\n✓ Word '%s' inserted successfully!\n", word);
                        } else {
                            printf("\n❌ Failed to insert word.\n");
                        }
                    }
                }
                break;
                
            case 3: // Save dictionary
                printf("\nSaving dictionary to '%s'...\n", dict_file);
                if (save_dictionary(root, dict_file)) {
                    printf("✓ Dictionary saved successfully!\n");
                } else {
                    printf("❌ Failed to save dictionary.\n");
                }
                break;
                
            case 4: // Exit
                printf("\nSaving dictionary before exit...\n");
                save_dictionary(root, dict_file);
                printf("\nCleaning up memory...\n");
                free_trie(root);
                printf("✓ Goodbye!\n\n");
                return 0;
                
            default:
                printf("\n❌ Invalid choice! Please select 1-4.\n");
        }
    }
    
    return 0;
}
