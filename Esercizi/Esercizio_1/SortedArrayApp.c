#include "ArrayLibrary.h"
#include "SortedArray.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ERROR_EXIT_CODE 1


// Defines the type of records read from file
typedef struct {
    int   id;
    char* field1;
    int   field2;
    float field3;
} Record;

// Options accepted by this program
typedef struct {
    Compare comparison_fun;         // comparison function to be used 
                                    // when initialising the SortedArray
    char const* filename;           // name of the file to be read
    char letter;
} Options;

int compare_string(Record* rec1, Record* rec2) {
    return strcoll(rec1->field1, rec2->field1);
}

int compare_int(Record* rec1, Record* rec2) {
    return rec1->field2 - rec2->field2;
}

int compare_float(Record* rec1, Record* rec2){
    if(rec1->field3 > rec2->field3)
        return 1;
    else if(rec1->field3 == rec2->field3)
        return 0;
    else return -1;    
}

void print_usage() {
    printf("sorted_array_app < -1 | -2 | -3 > <filename>\n");
    printf("    -1: sort according to the strings \n");
    printf("    -2: sort according to the ints \n");
    printf("    -3: sort according to the foats\n");

}

Options parse_options(int argc, char const *argv[]) {
    if(argc != 3) {
        printf("Parameters error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    Options options;

    if( !strcmp(argv[1], "-1") ) {
        options.comparison_fun = (Compare) compare_string;
    } else if( !strcmp(argv[1], "-2" ) ) {
        options.comparison_fun = (Compare) compare_int;
    } else if(!strcmp(argv[1], "-3") ) {
        options.comparison_fun = (Compare) compare_float;
    } else {
        printf("Parameters error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    printf("Press Q for Quicksort or I for InsertionSort\n");
    scanf("%c", &options.letter);

    options.filename = argv[2];

    return options;
}

void load_data(SortedArray* array, char const* filename, char letter) {
    double time_used;
    FILE* file = fopen(filename, "r");

    #define MAX_BUF_LEN 1024
    char string[MAX_BUF_LEN];
    float field3;
    int  field2, id;
    int lineno = 0;

    while(!feof(file)) {
        Record* record = (Record*) malloc(sizeof(Record));

        int n = fscanf(file, "%d,%1024[^ ,],%d,%f\n", &id, string, &field2, &field3);
        lineno++;

        if(n != 4) {
            if(feof(file)) {
                continue;
            }

            printf("Error while reading file at line: %d\n", lineno);
            exit(ERROR_EXIT_CODE);
        }

        record->id = id;
        record->field1 = strndup(string, MAX_BUF_LEN);
        record->field2 = field2;
        record->field3 = field3;

        SortedArrayInsert(array, record); 
    }

    printf("I dati sono stati letti e ci sono %2d righe caricate\n", lineno);
    clock_t start = clock();

    if(letter == 'Q')
        Quicksort(array, 0, Size(array)-1);
    else if(letter == 'I')
        InsertionSort(array);

    clock_t end = clock();  
    time_used = (double) (end - start) / CLOCKS_PER_SEC;
    printf("The total time for the sort is: %.6f seconds\n\n", time_used);       
}

void print_array(SortedArray* array) {
    for(int i=0; i<Size(array); ++i) {
        Record* rec = array->array[i];
        printf("id: %10d\tstr: %30s\tint: %10d\tfloat: %20f\n", rec->id, rec->field1, rec->field2, rec->field3 );
    }
}

void free_data(SortedArray* array) {
    for(int i=0; i<Size(array); ++i) {
        Record* rec = GetFromIndex(array, i);
        free(rec->field1);
        free(rec);
    }

    Free_SortedArray(array);
}

// Added this function who wasn't present in the standard libraries
char *strndup (const char *s, size_t n)
{
  size_t len = strnlen(s, n);
  char *new = (char *) malloc (len + 1);
  if (new == NULL)
    return NULL;
  new[len] = '\0';
  return (char *) memcpy (new, s, len);
}

// MAIN
// Usage: sorted_array_app < -1 | -2 | -3 > <filename>

int main(int argc, char const *argv[])
{
    
    Options options = parse_options(argc, argv);
    SortedArray* array = New_SortedArray(options.comparison_fun);
    load_data(array, options.filename, options.letter);
    free_data(array);

    return 0;
}
