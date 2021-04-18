
#include <stdio.h>
#include "string_vector.h"

void string_vector_print(StringVector *string_vec)
{
    printf("[ ");
    for (int i = 0; i < string_vec->len; i++)
    {
        printf("%s", string_vec->data[i]);
        if (i != string_vec->len - 1)
        {
            printf(", ");
        }
    }
    printf(" ]\n");
}
