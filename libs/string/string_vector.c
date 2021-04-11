#include <stdlib.h>
#include "string_utils.h"

void string_vector_free(string_vector string_vec)
{
    for (int i = 0; i < string_vec.len; i++)
    {
        free(*(string_vec.data + i));
    }
    free(string_vec.data);
}
