#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include "autocomplete.h"
#include "spellchecker.h" //including this to reuse the edit distace algorithm

void autocomplete(){
    FILE *fp=fopen("dict.txt","r");

    if(fp==NULL){
    printf("Cannot open dictionary file\n");
    return;
    }

wordmean *d=malloc(3000*sizeof(wordmean)); //multiplying by 3000 as we have 3000 words in our dictionary
if(d==NULL){
    printf("Memory allocation of words failed");
    fclose(fp);
    return;
    }

int count=0;
char *line=NULL;
size_t linelen=0;

char buffer[512];
while(fgets(buffer, sizeof(buffer), fp) != NULL){
    line[strcspn(line,"\n")]=0; //removing newline
    char *wordn=strtok(line,"|");
    char *meaningn=strtok(NULL,"|");

    if(wordn && meaningn){
        strcpy(d[count].word,wordn);
        strcpy(d[count].meaning,meaningn);
        count++;
    }
}
fclose(fp);
free(line);

//dynamic input
char input[100]="";
int inputlen=0;
int *distances=malloc(count*sizeof(int));

while(1){
    system("cls");
    printf("Type a word: %s\n", input);

    char ch=getch();
    if(ch==13) break; //enter
    if(ch==8){ //backspace
      if(inputlen>0){
       inputlen--;
       input[inputlen]='\0';
    }
}

else{
    input[inputlen++]=ch;
    input[inputlen]='\0';
}

//now computing edit distances of all words
if(inputlen>0){
for(int i=0;i<count;i++){
distances[i]=editdistance(input,d[i].word);
}
}

else {
    for(int i=0;i<count;i++)
        distances[i] = 1000; // large value, so no suggestion
}

//finding min distance
int sugg=0;
printf("Autocomplete suggestions:\n");
for(int dist=0;dist<1000 && sugg<MAX_SUGG;dist++){
    for(int i=0;i<count && sugg<MAX_SUGG;i++){
        if(distances[i]==dist){
            printf("%s - %s\n", d[i].word, d[i].meaning);
            sugg++;
        }
    }
}
if(sugg==0)
printf("No suggestions\n");

printf("\n");
fflush(stdout);
}

free(d);
free(distances);
}


static void collect_words(TrieNode *node, char *prefix, int level, char suggestions[][256], int *count, int max) {
    if (!node || *count >= max) return;

    if (node->is_end_of_word) {
        prefix[level] = '\0';
        strcpy(suggestions[*count], prefix);
        (*count)++;
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            prefix[level] = 'a' + i;
            collect_words(node->children[i], prefix, level + 1, suggestions, count, max);
        }
    }
}

// GUI autocomplete function
int autocomplete_gui(TrieNode *root, const char *prefix, char suggestions[][256], int max_suggestions) {
    if (!root || !prefix) return 0;

    TrieNode *node = root;
    int len = strlen(prefix);

    // Navigate to the prefix node
    for (int i = 0; i < len; i++) {
        int index = prefix[i] - 'a';
        if (index < 0 || index > 25 || !node->children[index])
            return 0;
        node = node->children[index];
    }

    // Collect all words with this prefix
    char buffer[256];
    strcpy(buffer, prefix);
    int count = 0;
    collect_words(node, buffer, len, suggestions, &count, max_suggestions);

    return count;
}

