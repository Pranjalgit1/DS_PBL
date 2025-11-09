#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "dictionary.h"

#define MAX_SUGG 5

typedef struct wordmean{
    char word[50];
    char meaning[50];
}wordmean;

void autocomplete(void);

int autocomplete_gui(TrieNode *root, const char *prefix, char suggestions[][256], int max_suggestions);

#endif
