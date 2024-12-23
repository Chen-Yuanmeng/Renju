#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include <stdint.h>

#define TABLE_SIZE 1024

typedef struct HashNode {
    unsigned long long key;
    int value;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode* table[TABLE_SIZE];
} HashTable;

int hash(unsigned long long key);
HashNode* create_node(unsigned long long key, int value);
HashTable* create_hashtable();
void insert_node(HashTable* ht, unsigned long long key, int value);
int search_node(HashTable* ht, unsigned long long key);
void delete_node(HashTable* ht, unsigned long long key);
void destroy_hashtable(HashTable* ht);

#endif
