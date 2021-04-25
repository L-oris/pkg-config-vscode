#include <assert.h>
#include <stdio.h>
#include "string_vec.h"

int main()
{
    printf("string_vec_uniq - should remove all duplicates");
    StringVec names = string_vec_new();
    string_vec_push(&names, "John");
    string_vec_push(&names, "Doe");
    string_vec_push(&names, "Mary");
    string_vec_push(&names, "Doe");
    string_vec_push(&names, "James");
    string_vec_push(&names, "James");
    string_vec_push(&names, "John");

    string_vec_uniq(&names);

    assert(names.len == 4);
    assert(string_vec_includes(&names, "John") == true);
    assert(string_vec_includes(&names, "Doe") == true);
    assert(string_vec_includes(&names, "Mary") == true);
    assert(string_vec_includes(&names, "James") == true);
    assert(string_vec_includes(&names, "Tony") == false);
    string_vec_free(names);
}
