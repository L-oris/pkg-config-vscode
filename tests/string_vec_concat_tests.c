#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "string_vec.h"

int main()
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
    string_vec_free(dst);
}
