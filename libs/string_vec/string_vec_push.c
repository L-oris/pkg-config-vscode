
#include <stdlib.h>
#include <string.h>
#include "string_vec.h"

void string_vec_push(StringVec *string_vec, char *str)
{
    char *owned_str = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(owned_str, str);

    string_vec->data = realloc(string_vec->data, string_vec->len + 1);
    string_vec->len += 1;

    string_vec->data[string_vec->len - 1] = owned_str;
}
