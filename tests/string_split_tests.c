#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "string_utils.h"

int main()
{
    printf("string_split - should return multiple items if delimiters are found\n");
    StringVec substr_a = string_split("Lorem ipsum dolor sit amet", ' ');
    assert(substr_a.len == 5);
    assert(strcmp(substr_a.data[0], "Lorem") == 0);
    assert(strcmp(substr_a.data[4], "amet") == 0);
    string_vec_free(substr_a);

    printf("string_split - should return a single item if no delimiter is found\n");
    StringVec substr_b = string_split("hello world", '-');
    assert(substr_b.len == 1);
    assert(strcmp(substr_b.data[0], "hello world") == 0);
    string_vec_free(substr_b);
}
