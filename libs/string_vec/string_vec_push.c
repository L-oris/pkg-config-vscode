#include <stdlib.h>
#include <string.h>
#include "string_vec.h"

void string_vec_push(StringVec *string_vec, char *str)
{
    char *owned_str = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(owned_str, str);

    int new_len = string_vec->len + 1;
    char **new_data = realloc(string_vec->data, sizeof(char *) * new_len);
    new_data[new_len - 1] = owned_str;

    string_vec->len = new_len;
    string_vec->data = new_data;
}
