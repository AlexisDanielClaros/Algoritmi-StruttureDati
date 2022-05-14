#include "hmLibrary.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define DEFAULT_TABLE_CAPACITY 100

struct hashNode 
{
    void* key;
    void* val;
    struct hashNode* next;
};

struct hashMap
{
    hashNode **table;
    int size;
    int capacity;
    Type type;
    Compare compare;
};


int numericHash(int key,int capacity){
    return (capacity * fmod((key * (sqrt(5)-1)/2), 1)); // multiplication hash
}

int stringHash(char* key,int capacity){
    unsigned long i = 0;
    for (int j=0; key[j]; j++)
        i += key[j];
    return i % capacity;
}


int compare_string(hashNode* node1, hashNode* node2) {
    return strcoll(node1->key, node2->key);
}

int compare_int(hashNode* node1, hashNode* node2) {
    return node1->key - node2->key;
}

int compare_float(hashNode* node1, hashNode* node2){
    if(node1->key > node2->key)
        return 1;
    else if(node1->key == node2->key)
        return 0;
    else return -1;    
}


hashMap* new_hm(){
    hashMap* newHm = (hashMap*) malloc(sizeof(hashMap));
    newHm->capacity = DEFAULT_TABLE_CAPACITY;
    newHm->size = 0;
    newHm->table = (hashNode**) malloc(sizeof(hashNode*) * newHm->capacity);
    for (int i=0; i<newHm->capacity; i++)
        newHm->table[i] = NULL;

    return newHm;
}

void resize_hm(hashMap* table){
    int oldCapacity = table->capacity;
    hashMap* newHm = (hashMap*) malloc(sizeof(hashMap));
    table->capacity *= 2;
    newHm->size = 0;
    newHm->type = table->type;
    newHm->capacity = table->capacity;
    newHm->compare = table->compare;
    newHm->table = (hashNode**) malloc(sizeof(hashNode*) * newHm->capacity);
    for (int i=0; i<newHm->capacity; i++)
        newHm->table[i] = NULL;
    for (int j=0; j<oldCapacity; j++){
        hashNode* node = table->table[j];
        while(node != NULL){
            insert_Node(newHm, node->key, node->val);
            node = node->next;
        }
    }
    free(table->table);
    table->table = newHm->table;
}

hashNode* set(hashMap* table, void* key, void* val){
        hashNode* node =(hashNode*) malloc(sizeof(hashNode));
        table->size++;

        node->key = key;
        node->val = val;
        node->next = NULL;

        return node;
}


void insert_Node(hashMap* table, void* key, void* val){
    int pos = table->type(key, table->capacity);
    hashNode* node = table->table[pos];
    if(node == NULL){  // If the position is empty, just put there the node
        table->table[pos] = set(table, key, val);
    } else{
        hashNode* prev;   
        while(node != NULL){
            // Else if the node already exist, change the value
            if(node->key == key){
                free(node->val);
                node->val =(void*) malloc(sizeof(void*));
                node->val = val;
                return;
            }
            prev = node;
            node = prev->next;
        }
        // Go forward in the list and add the new node at the end
        prev->next = set(table, key, val);
    }
    int filled = table->capacity * 0.75;
    if(table->size >= filled){ // If the capacity reach the 75% of the hashmap, resize it 
        resize_hm(table);
    }
}

void* get_value(hashMap* table, void* key){
    int pos = table->type(key, table->capacity);
    hashNode* node = table->table[pos];

    if(node == NULL)
        return NULL;

    while(node != NULL){
        if(node->key == key)
            return node->val;
        node = node->next;    
    }
    return NULL;    
}

void delete_element(hashMap* table, void* key){
    int pos = table->type(key, table->capacity);
    hashNode* node = table->table[pos];

    if(node == NULL){
        return;
    }
    int index = 0;
    hashNode* prev;
    while(node != NULL){
        if(node->key == key){
            // Case where is the first node
            if(node->next == NULL && index == 0)
                table->table[pos] = NULL;
            // Case where is the final node    
            else if(node->next == NULL && index != 0)
                prev->next = NULL;
            // Case where the node is first but is linked to another one    
            else if(node->next != NULL && index == 0)
                table->table[pos] = node->next;
            // Case where the node is in the middle        
            else if(node->next != NULL && index != 0)
                prev->next = node->next;

            // When found, delete it     
            free(node->key);
            free(node->val);
            free(node->next);
            table->size--;
            return;            
        }
        prev = node; 
        node = node->next;
        index++;
    }
}

void destroy_hm(hashMap* table){
    for (int i=0; i<table->capacity; i++) {
        hashNode* node = table->table[i];
        while(node != NULL){
            hashNode* next = node->next;
            delete_element(table, node->key);
            node = next;
        }
    }
    free(table->table);
    free(table);
}

int is_empty(hashMap* table){
    if(table->size > 0){
        return 1;
    }
    else if(table->size == 0){
        return 0;
    }
    else{ 
        return -1;
    }        
}


void* get_all_keys(hashMap* table){
    hashNode* node;
    void* array[table->size];
    int i = 0;
    int j = 0;

    for(; i<table->size; i++){
        node = table->table[i];
        j = i;
        while(node != NULL){
            array[j] = &node->key;
            node = node->next;
            j++;
        }
        i = j;
    }

    return *array;
}

int number_of_nodes(hashMap* table){
   return table->size;
}

int is_inside(hashMap* table, void* key){
    int pos = table->type(key, table->capacity);
    hashNode* node = table->table[pos];

    while(node != NULL){
        if(node->key == key)
            return 0;
        node = node->next;
    }    
    return -1;
}
