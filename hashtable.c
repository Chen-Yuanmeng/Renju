#include "hashtable.h"


int hash(unsigned long long key) {
    return key >> 54;
}

HashNode* create_node(unsigned long long key, Pair value) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

HashTable* create_hashtable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; ++i) {
        ht->table[i] = NULL;
    }
    return ht;
}

void insert_node(HashTable* ht, unsigned long long key, Pair value) {
    int index = hash(key);
    HashNode* newNode = create_node(key, value);

    // Insert at the beginning of the linked list
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

// Return `0` if found, `-1` if not found
// If found, the value will be stored in the `value` pointer
int search_node(HashTable* ht, unsigned long long key, Pair *value) {
    int index = hash(key);
    HashNode* current = ht->table[index];
    
    while (current != NULL) {
        if (current->key == key) {
            *value = current->value;
            return 0;  // Found
        }
        current = current->next;
    }
    
    return -1; // Not found
}

void delete_node(HashTable* ht, unsigned long long key) {
    int index = hash(key);
    HashNode* current = ht->table[index];
    HashNode* prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void destroy_hashtable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* current = ht->table[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht);
}