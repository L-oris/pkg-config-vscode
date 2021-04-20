#include <stdlib.h>
#include <string.h>
#include "std_string.h"

StdString std_string_init(char *src)
{
    char *data = malloc(sizeof(char) * (strlen(src)) + 1);
    strcpy(data, src);
    StdString str = {
        .data = data,
    };
    return str;
}
