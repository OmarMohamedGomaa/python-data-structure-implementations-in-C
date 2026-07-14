#include "dictionaries.h"
#include "list.h"
#include "tuples.h"
#include <stdio.h>

int main(void)
{
    printf("=== Dictionary demo ===\n");
    dict sample = Dictionary(2, "name", string, "Ada", "age", integer, 37);
    insert(&sample, "score", floating, 98.5);

    printf("Lookup name: %s\n", (char *)dict_get(&sample, "name"));
    printf("Lookup age: %d\n", *(int *)dict_get(&sample, "age"));
    printf("Type of 'score': %d\n", typeOffEntry(&sample, "score"));

    dict_remove(&sample, "age");
    printf("After removal, age found? %s\n", dict_get(&sample, "age") == NULL ? "no" : "yes");
    printf("Dictionary entry count: %d\n", sample.key_count);

    printf("\n=== List demo ===\n");
    list values = tolist(3, integer, 7, string, "hello", floating, 2.25);
    insertAt(&values, 1, string, "world");
    display_list(&values);

    printf("\n=== Tuple demo ===\n");
    tuple item = makeTuple(3, string, "north", integer, 11, floating, 4.5);
    displayTuple(&item);

    return 0;
}
