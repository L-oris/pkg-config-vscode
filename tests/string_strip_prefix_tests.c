#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "string_utils.h"

int main()
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
