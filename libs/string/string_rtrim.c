#include <ctype.h>
#include <string.h>

char *string_rtrim(char *str)
{
    char *back = str + strlen(str);
    while (isspace(*--back))
        ;
    *(back + 1) = '\0';
    return str;
}
