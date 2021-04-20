
#include <stdio.h>
#include "string_vec.h"

void string_vec_print(StringVec *string_vec)
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
