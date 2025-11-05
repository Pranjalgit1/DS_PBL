#include "heap.h"
#include <stdio.h>
unsigned int hash(const char* word) {
    unsigned int hash_val = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        hash_val = 37 * hash_val + word[i];
    }
    return hash_val % HASH_SIZE;
}

HashMap* create_hash_map() {
    HashMap* map = malloc(sizeof(HashMap));
    map->table = calloc(HASH_SIZE, sizeof(HashEntry*));
    return map;
}

void insert_hash(HashMap* map, const char* word, int index) {
    unsigned int key = hash(word);
    HashEntry* entry = malloc(sizeof(HashEntry));
    strcpy(entry->word, word);
    entry->heap_index = index;
    entry->next = map->table[key];
    map->table[key] = entry;
}

int find_heap_index(HashMap* map, const char* word) {
    unsigned int key = hash(word);
    HashEntry* entry = map->table[key];
    while (entry) {
        if (strcmp(entry->word, word) == 0) {
            return entry->heap_index;
        }
        entry = entry->next;
    }
    return -1;
}

void update_heap_index(HashMap* map, const char* word, int new_index) {
    unsigned int key = hash(word);
    HashEntry* entry = map->table[key];
    while (entry) {
        if (strcmp(entry->word, word) == 0) {
            entry->heap_index = new_index;
            return;
        }
        entry = entry->next;
    }
}

void free_hash_map(HashMap* map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashEntry* entry = map->table[i];
        while (entry) {
            HashEntry* temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    free(map->table);
    free(map);
}

MaxHeap* create_max_heap() {
    MaxHeap* heap = malloc(sizeof(MaxHeap));
    heap->array = malloc(HEAP_CAPACITY * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = HEAP_CAPACITY;
    return heap;
}

void swap_nodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MaxHeap* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->array[index].freq > heap->array[parent].freq) {
            swap_nodes(&heap->array[index], &heap->array[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapify_down(MaxHeap* heap, int index) {
    int left, right, largest;
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        largest = index;

        if (left < heap->size && heap->array[left].freq > heap->array[largest].freq) {
            largest = left;
        }
        if (right < heap->size && heap->array[right].freq > heap->array[largest].freq) {
            largest = right;
        }
        if (largest != index) {
            swap_nodes(&heap->array[index], &heap->array[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

void insert_heap(MaxHeap* heap, HashMap* map, const char* word, int freq) {
    if (heap->size == heap->capacity) {
        printf("Heap full! Implement resizing.\n");
        return;
    }
    int index = heap->size++;
    strcpy(heap->array[index].word, word);
    heap->array[index].freq = freq;
    insert_hash(map, word, index);
    heapify_up(heap, index);
}

void increase_freq(MaxHeap* heap, HashMap* map, const char* word, int increment) {
    int index = find_heap_index(map, word);
    if (index == -1) {
        insert_heap(heap, map, word, increment);
    } else {
        heap->array[index].freq += increment;
        heapify_up(heap, index); 
    }
}

HeapNode extract_max(MaxHeap* heap, HashMap* map) {
    if (heap->size == 0) {
        HeapNode empty = {"", -1};
        return empty;
    }
    HeapNode max = heap->array[0];
    heap->array[0] = heap->array[--heap->size];
    update_heap_index(map, heap->array[0].word, 0);
    heapify_down(heap, 0);
    return max;
}