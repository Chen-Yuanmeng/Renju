#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include <stdint.h>
#include <stdlib.h>

#define TABLE_SIZE 1024

typedef struct _Pair {
    int score_black;    // score in the perspective of black
    int score_white;    // score in the perspective of white
} Pair;

typedef struct HashNode {
    unsigned long long key;
    Pair value;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode* table[TABLE_SIZE];
} HashTable;

int hash(unsigned long long key);
HashNode* create_node(unsigned long long key, Pair value);
HashTable* create_hashtable();
void insert_node(HashTable* ht, unsigned long long key, Pair value);
int search_node(HashTable* ht, unsigned long long key, Pair *value);
void delete_node(HashTable* ht, unsigned long long key);
void destroy_hashtable(HashTable* ht);

#endif
