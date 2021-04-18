
#include <stdlib.h>
#include <string.h>
#include "string_vector.h"

void string_vector_push(StringVector *string_vec, char *str)
{
    char *owned_str = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(owned_str, str);

    string_vec->data = realloc(string_vec->data, string_vec->len + 1);
    string_vec->len += 1;

    string_vec->data[string_vec->len - 1] = owned_str;
}
