#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_vec.h"

int main()
{
    printf("string_vec_push - should append a new string\n");
    StringVec vec_a = string_vec_new();
    string_vec_push(&vec_a, "Foo");
    string_vec_push(&vec_a, "Bar");
    assert(strcmp(vec_a.data[0], "Foo") == 0);
    assert(strcmp(vec_a.data[1], "Bar") == 0);
    string_vec_free(vec_a);

    printf("string_vec_push - should increase vector's len\n");
    StringVec vec_b = string_vec_new();
    assert(vec_b.len == 0);
    string_vec_push(&vec_b, "a name");
    assert(vec_b.len == 1);
    string_vec_free(vec_b);

    printf("string_vec_push - should not break if the string argument is freed after push\n");
    StringVec vec_c = string_vec_new();
    char *name = malloc(sizeof(char) * (strlen("John Doe")));
    strcpy(name, "John Doe");
    string_vec_push(&vec_c, name);
    free(name);
    assert(strcmp(vec_c.data[0], "John Doe") == 0);
    string_vec_free(vec_c);
}
