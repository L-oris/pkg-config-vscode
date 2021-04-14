#include <stdlib.h>
#include <string.h>
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

void string_vector_map(string_vector *string_vec, int max_str_len, char *(*fp)(char *))
{
    char buffer[max_str_len];
    char *updated_buffer;
    for (int i = 0; i < string_vec->len; i++)
    {
        char *a_compiler_flag = string_vec->data[i];
        strcpy(buffer, a_compiler_flag);
        free(a_compiler_flag);

        updated_buffer = fp(buffer);

        char *heap_updated_buffer = malloc(sizeof(char) * strlen(updated_buffer) + 1);
        strcpy(heap_updated_buffer, updated_buffer);

        string_vec->data[i] = heap_updated_buffer;
    }
}
