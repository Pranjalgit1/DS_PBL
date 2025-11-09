#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#ifdef _WIN32
#include<conio.h>
#endif
#include "autocomplete.h"
#include "dictionary.h"
#include "spellchecker.h"

static void collect_words(TrieNode *node, char *prefix, int level, char suggestions[][256], int *count, int max) {
    if (!node || *count >= max) return;

    if (node->is_end_of_word) {
        prefix[level] = '\0';
        strcpy(suggestions[*count], prefix);
        (*count)++;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            prefix[level] = 'a' + i;
            collect_words(node->children[i], prefix, level + 1, suggestions, count, max);
        }
    }
}

static void to_lowercase_auto(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int autocomplete_suggestions(TrieNode *root, const char *prefix, char suggestions[][256], int max_suggestions) {
    if (!root || !prefix) return 0;

    char prefix_lower[256];
    strncpy(prefix_lower, prefix, sizeof(prefix_lower) - 1);
    prefix_lower[sizeof(prefix_lower) - 1] = '\0';
    to_lowercase_auto(prefix_lower);
    
    int len = strlen(prefix_lower);
    if (len == 0) return 0;

    TrieNode *node = root;

    for (int i = 0; i < len; i++) {
        if (!isalpha((unsigned char)prefix_lower[i])) continue;
        
        int index = prefix_lower[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE || !node->children[index])
            return 0;
        node = node->children[index];
    }

    char buffer[256];
    strcpy(buffer, prefix_lower);
    int count = 0;
    collect_words(node, buffer, len, suggestions, &count, max_suggestions);

    return count;
}

int autocomplete_gui(TrieNode *root, const char *prefix, char suggestions[][256], int max_suggestions) {
    return autocomplete_suggestions(root, prefix, suggestions, max_suggestions);
}

#ifdef _WIN32
void autocomplete(){
    FILE *fp=fopen("dictionary.txt","r");

    if(fp==NULL){
        printf("Cannot open dictionary file\n");
        return;
    }

    wordmean *d=malloc(3000*sizeof(wordmean));
    if(d==NULL){
        printf("Memory allocation of words failed\n");
        fclose(fp);
        return;
    }

    int count=0;
    char buffer[512];
    
    while(fgets(buffer, sizeof(buffer), fp) != NULL && count < 3000){
        buffer[strcspn(buffer,"\n")] = 0;
        char *wordn = strtok(buffer,"|");
        char *meaningn = strtok(NULL,"|");

        if(wordn && meaningn){
            strncpy(d[count].word, wordn, 49);
            d[count].word[49] = '\0';
            strncpy(d[count].meaning, meaningn, 49);
            d[count].meaning[49] = '\0';
            count++;
        }
    }
    fclose(fp);

    char input[100]="";
    int inputlen=0;
    int *distances=malloc(count*sizeof(int));
    
    if(!distances){
        printf("Memory allocation failed\n");
        free(d);
        return;
    }

    printf("\n=== AUTOCOMPLETE MODE ===\n");
    printf("Type letters and see suggestions in real-time!\n");
    printf("Press ENTER to exit, BACKSPACE to delete\n\n");

    while(1){
        system("cls");
        printf("=== AUTOCOMPLETE MODE ===\n");
        printf("Type a word: %s\n", input);
        printf("(Press ENTER to exit)\n\n");

        char ch=getch();
        if(ch==13) break;
        if(ch==8){
            if(inputlen>0){
                inputlen--;
                input[inputlen]='\0';
            }
        }
        else if(isalpha(ch)){
            input[inputlen++]=ch;
            input[inputlen]='\0';
        }

        if(inputlen>0){
            for(int i=0;i<count;i++){
                distances[i]=editdistance(input,d[i].word);
            }
        }
        else {
            for(int i=0;i<count;i++)
                distances[i] = 1000;
        }

        int sugg=0;
        printf("Autocomplete suggestions:\n");
        printf("========================================\n");
        for(int dist=0;dist<5 && sugg<MAX_SUGG;dist++){
            for(int i=0;i<count && sugg<MAX_SUGG;i++){
                if(distances[i]==dist){
                    printf("%d. %s - %s\n", sugg+1, d[i].word, d[i].meaning);
                    sugg++;
                }
            }
        }
        if(sugg==0)
            printf("No suggestions found\n");
        
        printf("========================================\n");
        fflush(stdout);
    }

    free(d);
    free(distances);
    printf("\nExiting autocomplete mode...\n");
}
#else
void autocomplete(){
    printf("Interactive autocomplete is only available on Windows (requires conio.h)\n");
    printf("Use option 4 'Autocomplete a word' from the main menu instead.\n");
}
#endif

