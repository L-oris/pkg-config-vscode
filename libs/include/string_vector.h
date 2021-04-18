#pragma once

typedef struct _StringVector
{
    char **data;
    int len;
} StringVector;

void string_vector_free(StringVector string_vec);

StringVector string_vector_new();

void string_vector_map(StringVector *string_vec, int max_str_len, char *(*fp)(char *));
