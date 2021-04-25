#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "string_utils.h"

int main()
{
    printf("string_starts_with - should return false if the string doesn't start with the provided pattern\n");
    assert(string_starts_with("hello world", "world") == false);

    printf("string_starts_with - should return true if the string starts with the provided pattern\n");
    assert(string_starts_with("hello world", "hello") == true);
}
