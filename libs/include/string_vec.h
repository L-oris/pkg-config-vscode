#pragma once
#include <stdbool.h>

typedef struct _StringVec
{
    char **data;
    int len;
} StringVec;

void string_vec_free(StringVec string_vec);

StringVec string_vec_new();

void string_vec_push(StringVec *string_vec, char *str);

void string_vec_map(StringVec *string_vec, int max_str_len, char *(*fp)(char *));

void string_vec_concat(StringVec *dst, StringVec src);

bool string_vec_includes(StringVec *string_vec, char *str);

void string_vec_print(StringVec *string_vec);
