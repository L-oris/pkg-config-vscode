#include <stdio.h>
#include <string.h>
#include "string_utils.h"

char *string_strip_prefix(char *src_string, char *prefix)
{
    if (!string_starts_with(src_string, prefix))
    {
        return NULL;
    }

    char *ret = src_string + strlen(prefix);
    return ret;
}
