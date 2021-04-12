#include <stdlib.h>
#include "string_utils.h"

string_vector string_vector_empty()
{
    string_vector ret = {
        .data = NULL,
        .len = 0};
    return ret;
}

void string_vector_free(string_vector string_vec)
{
    for (int i = 0; i < string_vec.len; i++)
    {
        free(*(string_vec.data + i));
    }
    free(string_vec.data);
}
