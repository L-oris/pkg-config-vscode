#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_vector.h"

void string_vector_push_tests()
{
    printf("string_vector_push - should append a new string\n");
    StringVector vec_a = string_vector_new();
    string_vector_push(&vec_a, "Foo");
    string_vector_push(&vec_a, "Bar");
    assert(strcmp(vec_a.data[0], "Foo") == 0);
    assert(strcmp(vec_a.data[1], "Bar") == 0);
    string_vector_free(vec_a);

    printf("string_vector_push - should increase vector's len\n");
    StringVector vec_b = string_vector_new();
    assert(vec_b.len == 0);
    string_vector_push(&vec_b, "a name");
    assert(vec_b.len == 1);
    string_vector_free(vec_b);

    printf("string_vector_push - should not break if the string argument is freed after push\n");
    StringVector vec_c = string_vector_new();
    char *name = malloc(sizeof(char) * (strlen("John Doe")));
    strcpy(name, "John Doe");
    string_vector_push(&vec_c, name);
    free(name);
    assert(strcmp(vec_c.data[0], "John Doe") == 0);
    string_vector_free(vec_c);
}

void string_vector_concat_tests()
{
    printf("string_vector_concat - should merge src into dst");
    StringVector dst = string_vector_new();
    string_vector_push(&dst, "John");
    StringVector src = string_vector_new();
    string_vector_push(&src, "Doe");
    string_vector_push(&src, "Ball");

    string_vector_concat(&dst, src);
    assert(dst.len == 3);
    assert(strcmp(dst.data[0], "John") == 0);
    assert(strcmp(dst.data[1], "Doe") == 0);
    assert(strcmp(dst.data[2], "Ball") == 0);
}

void string_vector_includes_tests()
{
    printf("string_vector_includes - should work as expected");
    StringVector names = string_vector_new();
    string_vector_push(&names, "John");
    string_vector_push(&names, "Doe");

    assert(string_vector_includes(&names, "Doe") == true);
    assert(string_vector_includes(&names, "Tom") == false);
}

int main()
{
    string_vector_push_tests();
    string_vector_concat_tests();
    string_vector_includes_tests();
}
