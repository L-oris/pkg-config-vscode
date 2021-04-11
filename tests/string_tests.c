#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "string_utils.h"

void string_split_tests()
{
    string_vector substr;

    printf("string_split - should return a single item if no delimiter is found\n");
    substr = string_split("hello world", '-');
    assert(substr.len == 1);
    assert(strcmp(substr.data[0], "hello world") == 0);

    printf("string_split - should return multiple items if delimiters are found\n");
    substr = string_split("Lorem ipsum dolor sit amet", ' ');
    assert(substr.len == 5);
    assert(strcmp(substr.data[0], "Lorem") == 0);
    assert(strcmp(substr.data[4], "amet") == 0);
}

void string_starts_with_tests()
{
    printf("string_starts_with - should return false if the string doesn't start with the provided pattern\n");
    assert(string_starts_with("hello world", "world") == false);

    printf("string_starts_with - should return true if the string starts with the provided pattern\n");
    assert(string_starts_with("hello world", "hello") == true);
}

void string_strip_prefix_tests()
{
    printf("string_strip_prefix - should return a NULL pointer if the source string doesn't start with prefix\n");
    assert(string_strip_prefix("smartphone", "hello") == NULL);

    printf("string_strip_prefix - should return the trimmed string\n");
    char *trimmed_string = string_strip_prefix("smartphone", "smart");
    assert(strcmp(trimmed_string, "phone") == 0);

    printf("string_strip_prefix - should not modify the source string\n");
    char *src_string = "tree";
    string_strip_prefix(src_string, "tr");
    assert(strcmp(src_string, "tree") == 0);
}

int main()
{
    string_split_tests();
    string_starts_with_tests();
    string_strip_prefix_tests();
}
