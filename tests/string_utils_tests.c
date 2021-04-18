#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "string_utils.h"

void string_split_tests()
{
    StringVector substr;

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

void string_rtrim_tests()
{
    char *result;

    printf("string_rtrim - should return the original string if no characters need to be trimmed\n");
    char test_str_a[] = "hello world";
    result = string_rtrim(test_str_a);
    assert(strcmp(result, test_str_a) == 0);

    printf("string_rtrim - should not modify the source string if no characters need to be trimmed\n");
    char test_str_b[] = "hello world";
    string_rtrim(test_str_b);
    assert(strcmp("hello world", test_str_b) == 0);

    printf("string_rtrim - should trim space characters on the right\n");
    char test_str_c[] = "hello world\n";
    result = string_rtrim(test_str_c);
    assert(strcmp(result, "hello world") == 0);

    printf("string_rtrim - should modify the source string if characters need to be trimmed\n");
    char test_str_d[] = "hello world\n";
    string_rtrim(test_str_d);
    assert(strcmp("hello world", test_str_d) == 0);
}

int main()
{
    string_split_tests();
    string_starts_with_tests();
    string_strip_prefix_tests();
    string_rtrim_tests();
}
