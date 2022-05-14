#include "unity.h"
#include "hmLibrary.h"
#include "stdlib.h"

struct hashMap
{
    hashNode **table;
    int size;
    int capacity;
    Type type;
    Compare compare;
};

//functions to make unity work
void setUp (void) {}
void tearDown (void) {}


int compare_ints(int* node1, int* node2) {
    return node1 - node2;
}

static hashMap* create_hm(){
    hashMap* hm = new_hm();
    hm->type = (Type) numericHash;
    hm->compare =(Compare) compare_ints;
    insert_Node(hm, (void*) 1, (void*) 10);
    insert_Node(hm, (void*) 2, (void*) 5);
    insert_Node(hm, (void*) 3, (void*) 0);
    insert_Node(hm, (void*) 4, (void*) 1);
    return hm;
}

static void empty_hm(){
    hashMap* hm = new_hm();
    TEST_ASSERT_EQUAL(0, is_empty(hm));
    destroy_hm(hm);
}

static void get_from_hm(){
    hashMap* hm = create_hm();
    TEST_ASSERT_EQUAL(10, (int) get_value(hm, (void*) 1));
    TEST_ASSERT_EQUAL(5, (int) get_value(hm, (void*) 2));
    TEST_ASSERT_EQUAL(0, (int) get_value(hm, (void*) 3));
    TEST_ASSERT_EQUAL(1, (int) get_value(hm, (void*) 4));
    destroy_hm(hm);
}

static void test_elements(){
    hashMap* hm = create_hm();
    TEST_ASSERT_EQUAL(0, is_inside(hm, (void*) 1));
    TEST_ASSERT_EQUAL(0, is_inside(hm, (void*) 2));
    TEST_ASSERT_EQUAL(4, number_of_nodes(hm));
    delete_element(hm, (void*) 1);
    delete_element(hm, (void*) 2);
    TEST_ASSERT_EQUAL(-1, is_inside(hm, (void*) 1));
    TEST_ASSERT_EQUAL(-1, is_inside(hm, (void*) 2));
    TEST_ASSERT_EQUAL(2, number_of_nodes(hm));
    destroy_hm(hm);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(empty_hm);
    RUN_TEST(get_from_hm);
    RUN_TEST(test_elements);

    UNITY_END();
}
