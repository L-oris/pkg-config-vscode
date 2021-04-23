#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_vec.h"

void string_vec_push_tests()
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

void string_vec_concat_tests()
{
    printf("string_vec_concat - should merge src into dst");
    StringVec dst = string_vec_new();
    string_vec_push(&dst, "John");
    StringVec src = string_vec_new();
    string_vec_push(&src, "Doe");
    string_vec_push(&src, "Ball");

    string_vec_concat(&dst, src);
    assert(dst.len == 3);
    assert(strcmp(dst.data[0], "John") == 0);
    assert(strcmp(dst.data[1], "Doe") == 0);
    assert(strcmp(dst.data[2], "Ball") == 0);
}

void string_vec_includes_tests()
{
    printf("string_vec_includes - should work as expected");
    StringVec names = string_vec_new();
    string_vec_push(&names, "John");
    string_vec_push(&names, "Doe");

    assert(string_vec_includes(&names, "Doe") == true);
    assert(string_vec_includes(&names, "Tom") == false);
}

void string_vec_uniq_tests()
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
}

int main()
{
    string_vec_push_tests();
    string_vec_concat_tests();
    string_vec_includes_tests();
    string_vec_uniq_tests();
}
