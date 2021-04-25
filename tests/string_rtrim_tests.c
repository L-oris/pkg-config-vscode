#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "string_utils.h"

int main()
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
