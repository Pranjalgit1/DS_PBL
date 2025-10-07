#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stddef.h>

typedef struct dictionary{
    char word[20];
    char meaning[100];
}dictionary;

int min(int a, int b, int c);

int editdistance(char *s1, char *s2);

void run_spellchecker(char *input, const char *dict_file);

#endif
