#include <stdbool.h>
#include <string.h>
#include "string_vector.h"

bool string_vector_includes(StringVector *string_vec, char *str)
{
    for (int i = 0; i < string_vec->len; i++)
    {
        char *curr = string_vec->data[i];
        if (strcmp(curr, str) == 0)
        {
            return true;
        }
    }
    return false;
}
