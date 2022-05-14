#include "unity.h"
#include "ArrayLibrary.h"
#include "stdlib.h"

//functions to make unity work
void setUp (void) {}
void tearDown (void) {}

static int* int_new(int n) {
    int* result = (int*) malloc(sizeof(int));
    *result = n;

    return result;
}

static int compareInts(int* obj1, int* obj2) {
    return *obj1 - *obj2;
}

static SortedArray* fill_the_array() {
    SortedArray* array = New_SortedArray((Compare) compareInts);
    SortedArrayInsert(array, int_new(1));
    SortedArrayInsert(array, int_new(2));
    SortedArrayInsert(array, int_new(3));
    SortedArrayInsert(array, int_new(4));
    return array;
}


static void delete_elements(SortedArray* array) {
    for(int i=0; i< Size(array); ++i) {
        Free_SortedArray(GetFromIndex(array, i));
    }

    Free_SortedArray(array);
}


static void empty_array() {
    SortedArray* array = New_SortedArray((Compare) compareInts);
    TEST_ASSERT_EQUAL(0, Size(array));

    Free_SortedArray(array);
}

static void get_from_array() {
    SortedArray* array = fill_the_array();

    TEST_ASSERT_EQUAL(1, *(int*) GetFromIndex(array, 0));
    TEST_ASSERT_EQUAL(2, *(int*) GetFromIndex(array, 1));
    TEST_ASSERT_EQUAL(3, *(int*) GetFromIndex(array, 2));
    TEST_ASSERT_EQUAL(4, *(int*) GetFromIndex(array, 3));

    delete_elements(array);
}

static void swap_elements(){
    SortedArray* array = fill_the_array();
    Swap(array, 0, 1);

    TEST_ASSERT_EQUAL(2, *(int*) GetFromIndex(array, 0));
    TEST_ASSERT_EQUAL(1, *(int*) GetFromIndex(array, 1));

    delete_elements(array);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(empty_array);
    RUN_TEST(get_from_array);
    RUN_TEST(swap_elements);

    UNITY_END();
}
