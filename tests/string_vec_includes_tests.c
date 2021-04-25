#include <assert.h>
#include <stdio.h>
#include "string_vec.h"

int main()
{
    printf("string_vec_includes - should work as expected");
    StringVec names = string_vec_new();
    string_vec_push(&names, "John");
    string_vec_push(&names, "Doe");

    assert(string_vec_includes(&names, "Doe") == true);
    assert(string_vec_includes(&names, "Tom") == false);
    string_vec_free(names);
}
