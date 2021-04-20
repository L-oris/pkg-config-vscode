#include <stdbool.h>
#include <string.h>
#include "string_vec.h"

bool string_vec_includes(StringVec *string_vec, char *str)
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
