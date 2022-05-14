#include <stddef.h> //for use size_t

typedef struct _SortedArray SortedArray;
typedef int (*Compare)(void*, void*);

// Create an array
SortedArray* New_SortedArray(Compare);

// Delete the array from the memory
void Free_SortedArray(SortedArray* array);

// Returns the size of the array
int Size(SortedArray* array);

// Add an element at the end of the array
void SortedArrayInsert(SortedArray* array, void* x);

// When needed, double the capacity of the array
void SortedArray_resize(SortedArray* array, size_t a);

// Get a position of an element
void* GetFromIndex(SortedArray* array, int i);

// Sort the array with the quicksort method
void Quicksort(SortedArray* array, int a, int b);

// Inside function of quicksort
void Partitioning(SortedArray* array, int first, int last, void* p,int *left, int *rigth);

// Swap two positions of an array
void Swap(SortedArray* array, int i, int j);

// Sort the array with the insertion sort method
void InsertionSort(SortedArray* array);
