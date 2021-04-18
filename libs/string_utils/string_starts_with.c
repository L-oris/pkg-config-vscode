#include <string.h>
#include <stdbool.h>
#include "string_utils.h"

bool string_starts_with(char *src_string, char *prefix)
{
    int result = strncmp(src_string, prefix, strlen(prefix));
    return result == 0;
}
