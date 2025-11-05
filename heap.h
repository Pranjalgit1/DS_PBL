#ifndef HEAP_H
#define HEAP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LEN 50 
#define HEAP_CAPACITY 1000 
#define HASH_SIZE 10007  

typedef struct {
    char word[MAX_WORD_LEN];
    int freq;
} HeapNode;

typedef struct {
    HeapNode* array; 
    int size;         
    int capacity;    
} MaxHeap;

typedef struct HashEntry {
    char word[MAX_WORD_LEN];
    int heap_index;  
    struct HashEntry* next;  
} HashEntry;

typedef struct {
    HashEntry** table; 
} HashMap;

MaxHeap* create_max_heap();
void free_max_heap(MaxHeap* heap);

HashMap* create_hash_map();
void free_hash_map(HashMap* map);

unsigned int hash(const char* word);
void insert_hash(HashMap* map, const char* word, int index);
int find_heap_index(HashMap* map, const char* word);
void update_heap_index(HashMap* map, const char* word, int new_index);
void insert_heap(MaxHeap* heap, HashMap* map, const char* word, int freq);
void increase_freq(MaxHeap* heap, HashMap* map, const char* word, int increment);
void heapify_up(MaxHeap* heap, HashMap* map, int index);
void heapify_down(MaxHeap* heap, HashMap* map, int index);
void swap_nodes(HeapNode* a, HeapNode* b);
HeapNode extract_max(MaxHeap* heap, HashMap* map);
void get_top_searched_words(MaxHeap* heap, int n);

#endif
