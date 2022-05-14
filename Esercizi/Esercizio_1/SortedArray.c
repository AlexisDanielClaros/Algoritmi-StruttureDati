#include "ArrayLibrary.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

// Structure with the array of Records and the specific function for compare
struct _SortedArray
{
    void** array;
    int size;
    int capacity;
    Compare compare;
};

SortedArray* New_SortedArray(Compare compare){
    SortedArray* newArray = (SortedArray*) malloc(sizeof(SortedArray));
    newArray->capacity = 10;
    newArray->array = (void**) malloc(sizeof(void*) * newArray->capacity);
    newArray->size = 0;
    newArray->compare = compare;

    return newArray;
}

// Add the element at the end of the array
void SortedArrayInsert(SortedArray* array, void* obj){
    if(array->capacity == array->size) {
        SortedArray_resize(array, array->capacity * 2);
    }
    int i = Size(array);
    array->array[i] = obj;
    array->size++;

}

void SortedArray_resize(SortedArray* array, size_t memsize) {
    array->capacity = memsize;
    array->array = (void**) realloc(array->array, sizeof(void*) * array->capacity);
}

void Free_SortedArray(SortedArray* array){
    free(array->array);
    free(array);
}

int Size(SortedArray* array){
    return array->size;
}

void* GetFromIndex(SortedArray* array, int i){
    return array->array[i];
}

void Swap(SortedArray* array, int i, int j){
    void* temp;
    temp = array->array[i];
    array->array[i] = array->array[j];
    array->array[j] = temp;
}

// It looks every element and shift to the rigth all the elements > pivot until it founds an element < pivot and puts in that position
void InsertionSort(SortedArray* array){
    int j, i;
    void* pivot;

    for(j = 1; j < array->size; j++){
        pivot =  array->array[j];
        i = j-1;
        while(i >= 0 && array->compare(array->array[i], pivot) > 0){
            array->array[i+1] = array->array[i];
            i--;
        }
        array->array[i+1] = pivot;
    }
}

// It separate the array in 2 subarray left and rigth with the pivot in the middle, and then sort left and rigth again 
void Quicksort(SortedArray* array, int first, int last){

    int left, rigth;
    void* pivot;

    if(first < last){
        pivot = array->array[last];
        Partitioning(array, first, last, pivot, &left, &rigth);
        Quicksort(array, first, left-1);
        Quicksort(array, rigth, last);
    }

}

// Sort the array in three parts the left with elements < pivot, mid with elements == pivot and rigth with elements > pivot 
// Set the positions on the *left of pivot and on the *rigth avoiding the elements == pivot (they are already sorted)
void Partitioning(SortedArray* array, int first, int last, void* p, int *left, int *rigth){
    int l = first;
    int r = first;
    int supp = last;
    int result;

    while (r <= supp){
        result = array->compare(array->array[r], p);
        if (result < 0){
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

