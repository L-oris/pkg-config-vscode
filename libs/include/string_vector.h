#pragma once
#include <stdbool.h>

typedef struct _StringVector
{
    char **data;
    int len;
} StringVector;

void string_vector_free(StringVector string_vec);

StringVector string_vector_new();

void string_vector_push(StringVector *string_vec, char *str);

void string_vector_map(StringVector *string_vec, int max_str_len, char *(*fp)(char *));

void string_vector_concat(StringVector *dst, StringVector src);

bool string_vector_includes(StringVector *string_vec, char *str);
