#include "heap.h"


unsigned int hash(const char* word) {
    unsigned int hash_val = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        hash_val = 37 * hash_val + word[i];
    }
    return hash_val % HASH_SIZE;
}


HashMap* create_hash_map() {
    HashMap* map = malloc(sizeof(HashMap));
    if (!map) return NULL;
    map->table = calloc(HASH_SIZE, sizeof(HashEntry*));
    if (!map->table) {
        free(map);
        return NULL;
    }
    return map;
}


void insert_hash(HashMap* map, const char* word, int index) {
    unsigned int key = hash(word);
    HashEntry* entry = malloc(sizeof(HashEntry));
    if (!entry) return;
    
    strncpy(entry->word, word, MAX_WORD_LEN - 1);
    entry->word[MAX_WORD_LEN - 1] = '\0';
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
    if (!map) return;
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
    if (!heap) return NULL;
    
    heap->array = malloc(HEAP_CAPACITY * sizeof(HeapNode));
    if (!heap->array) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = HEAP_CAPACITY;
    return heap;
}


void free_max_heap(MaxHeap* heap) {
    if (!heap) return;
    if (heap->array) free(heap->array);
    free(heap);
}


void swap_nodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}


void heapify_up(MaxHeap* heap, HashMap* map, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->array[index].freq > heap->array[parent].freq) {
            update_heap_index(map, heap->array[index].word, parent);
            update_heap_index(map, heap->array[parent].word, index);
            
            swap_nodes(&heap->array[index], &heap->array[parent]);
            index = parent;
        } else {
            break;
        }
    }
}


void heapify_down(MaxHeap* heap, HashMap* map, int index) {
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
            update_heap_index(map, heap->array[index].word, largest);
            update_heap_index(map, heap->array[largest].word, index);
            
            swap_nodes(&heap->array[index], &heap->array[largest]);
            index = largest;
        } else {
            break;
        }
    }
}


void insert_heap(MaxHeap* heap, HashMap* map, const char* word, int freq) {
    if (heap->size >= heap->capacity) {
        printf("Warning: Heap is full! Cannot insert '%s'\n", word);
        return;
    }
    
    int index = heap->size++;
    strncpy(heap->array[index].word, word, MAX_WORD_LEN - 1);
    heap->array[index].word[MAX_WORD_LEN - 1] = '\0';
    heap->array[index].freq = freq;
    
    insert_hash(map, word, index);
    heapify_up(heap, map, index);
}


void increase_freq(MaxHeap* heap, HashMap* map, const char* word, int increment) {
    int index = find_heap_index(map, word);
    if (index == -1) {
        insert_heap(heap, map, word, increment);
    } else {
        heap->array[index].freq += increment;
        heapify_up(heap, map, index); 
    }
}


HeapNode extract_max(MaxHeap* heap, HashMap* map) {
    if (heap->size == 0) {
        HeapNode empty = {"", -1};
        return empty;
    }
    HeapNode max = heap->array[0];
    heap->array[0] = heap->array[--heap->size];
    
    if (heap->size > 0) {
        update_heap_index(map, heap->array[0].word, 0);
        heapify_down(heap, map, 0);
    }
    return max;
}


void get_top_searched_words(MaxHeap* heap, int n) {
    if (!heap || heap->size == 0) {
        printf("\nNo search history available.\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("   TOP %d MOST SEARCHED WORDS\n", n);
    printf("========================================\n");
    
    int count = (n < heap->size) ? n : heap->size;
    
    HeapNode* temp = malloc(heap->size * sizeof(HeapNode));
    if (!temp) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    memcpy(temp, heap->array, heap->size * sizeof(HeapNode));
    int temp_size = heap->size;
    
    for (int i = 0; i < count; i++) {
        int max_idx = 0;
        for (int j = 1; j < temp_size; j++) {
            if (temp[j].freq > temp[max_idx].freq) {
                max_idx = j;
            }
        }
        
        printf("%2d. %-20s (searched %d times)\n", 
               i + 1, temp[max_idx].word, temp[max_idx].freq);
        
        temp[max_idx] = temp[temp_size - 1];
        temp_size--;
    }
    
    printf("========================================\n");
    free(temp);
}
