#include <stdlib.h>
#include "string_vector.h"

void string_vector_concat(StringVector *dst, StringVector src)
{
    dst->data = realloc(dst->data, sizeof(char *) * (dst->len + src.len));
    int src_curr_index = 0;
    for (int i = 0; i < src.len; i++)
    {
        dst->data[dst->len] = src.data[src_curr_index];
        dst->len += 1;
        src_curr_index += 1;
    }
    free(src.data);
}
