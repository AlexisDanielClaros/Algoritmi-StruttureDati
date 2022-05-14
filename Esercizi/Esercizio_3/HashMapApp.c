#include "hmLibrary.h"
#include "HashMap.c"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define KEYS 10000000
#define NODES 6321078


void set_hash_compare(hashMap* table, int argc, char const *argv[]){
    if(argc != 2) {
        printf("Parameters error\n");
        exit(1);
    }
    if( !strcmp(argv[1], "-1") ) {
        table->compare = (Compare) compare_string;
        table->type = (Type) stringHash;
    } else if( !strcmp(argv[1], "-2" ) ) {
        table->compare = (Compare) compare_int;
        table->type = (Type) numericHash;
    } else if( !strcmp(argv[1], "-3" ) ) {
        table->compare = (Compare) compare_float;
        table->type = (Type) numericHash;
    } else {
        printf("Parameters error\n");
        exit(1);
    }
}


// Same method used by the teacher
// This funtion load an hashmap
void load_data_hm(hashMap* table){
    FILE* file = fopen("hashes.csv", "r");
    void* key, *value;
    int lineno = 0;

    while(!feof(file)) {

        int n = fscanf(file, "%d,%d\n", &key, &value);
        lineno++;

        if(n != 2) {
            if(feof(file)) {
                continue;
            }
            printf("Error while reading file at line: %d\n", lineno);
            exit(1);
        }   
        insert_Node(table, key, value);

    }
}

// This load an array
void load_data_arr(hashNode* array[]){
    FILE* file = fopen("hashes.csv", "r");
    void* key, *value; 
    int i = 0;
    int lineno = 0;

    while(!feof(file)){
        hashNode* node =(hashNode*) malloc(sizeof(hashNode));

        int n = fscanf(file, "%d,%d\n", &key, &value);
        lineno++;

        if(n != 2) {
            if(feof(file)) {
                continue;
            }
            printf("Error while reading file at line: %d\n", lineno);
            exit(1);
        }

        node->key = key;
        node->val = value;
        node->next = NULL;  
        array[i] = node;
        i++;
    }

}


void Swap(hashNode* array[], int i, int j){
    hashNode* temp;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}


void Partitioning(hashNode* array[], int first, int last, hashNode* p, int *left, int *rigth, Compare compare){
    int l = first;
    int r = first;
    int supp = last;

    while (r <= supp){
        int result = compare(array[r], p);
        if (result < 0 ){
            Swap(array, l, r);
            l++;
            r++;
        }     
        else if (result > 0){
            Swap(array, r, supp);
            supp--;
        }
        else if(result == 0) r++;
        *rigth = r;
        *left = l;
    }
}

// Same quicksort used in the exercise 1
void Quicksort(hashNode* array[], int first, int last, Compare compare){
    hashNode* pivot;
    int left, rigth;
    
    if(first < last){
        pivot = array[last];
        Partitioning(array, first, last, pivot, &left, &rigth, compare);
        Quicksort(array, first, left-1, compare);
        Quicksort(array, rigth, last, compare);
    }
}



// Fill an array with random numbers
void rand_array(int* array){
    int i = 0;
    for(; i<KEYS; i++){
        array[i] = rand()%KEYS+1;
    }
}

int search_keys_hm(hashMap* hm, int keys[]){
    int result, count = 0, i = 0;
    for(; i<KEYS; i++){
        // Check if every key is inside the hashmap
        result = is_inside(hm, (void*) keys[i]);
        if(result != -1)
            count++;
    }
    return count;
}

int binary_search(hashNode* arr[], int left, int right, int key, Compare compare){
    if (right >= left) { 
        int mid = left + (right - left) / 2; 
        hashNode* node;
        node->key = (void*) key;
        int result = compare(arr[mid], node);
        // If the element is in the middle
        if (result == 0) 
            return 1; 
  
        // If the element is smaller than key, we search in the left side
        if (result > 0) 
            return binary_search(arr, left, mid - 1, key, compare); 
  
        // Else if it's bigger than mid, we search in the right side 
        return binary_search(arr, mid + 1, right, key, compare); 
    } 
    return -1;
} 


int search_keys_arr(hashNode* arr[], int keys[], Compare compare){
    int i = 0;
    int result, count = 0;
    for(; i<KEYS; i++){
        // Check if every key is inside the array
        result = binary_search(arr, 0, NODES-1, keys[i], compare);
        if(result != -1)
            count++;
    }
    return count;
}



int main(int argc, char const *argv[]){
    srand(time(0));  // Set the seed for the rand() function
    static hashNode* array[NODES];  
    double time_used;
    int result=0, count=0; // We'll store the number of keys found in the hashmap and array
    clock_t start = clock();
    static int keys[KEYS];
    hashMap* hm = new_hm();
    set_hash_compare(hm, argc, argv);
    
    rand_array(keys);
    load_data_arr(array);
    load_data_hm(hm);
    Quicksort(array, 0, NODES-1, hm->compare);
    count = search_keys_hm(hm,keys);
    result = search_keys_arr(array, keys,hm->compare);
    printf("Keys found in the hashmap: %d\nKeys found in the array: %d \n", count, result);
    clock_t end = clock();
    time_used = (double) (end - start) / CLOCKS_PER_SEC;
    printf("The total time for the loading is: %.6f seconds\n\n", time_used);
    return 0;    

}