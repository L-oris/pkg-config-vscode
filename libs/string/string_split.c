#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string_utils.h"

static int index_of_first_delimiter(char str[], char delimiter)
{
    char *ptr_to_ch = strchr(str, delimiter);
    if (ptr_to_ch == NULL)
    {
        return -1;
    }

    return ptr_to_ch - str;
}

static int count_delimiters(char str[], char delimiter)
{
    int count = 0;
    while (*str)
    {
        if (*str == delimiter)
        {
            count += 1;
        }
        str += 1;
    }
    return count;
}

string_vector string_split(char *src_string, char delimiter)
{
    int substrings_len = count_delimiters(src_string, delimiter) + 1;
    char **substrings = malloc(sizeof(char *) * substrings_len);

    int counter = 0;
    while (true)
    {
        char *substring;
        int index_of_found = index_of_first_delimiter(src_string, delimiter);
        if (index_of_found == -1)
        {
            substring = malloc(sizeof(char) * (strlen(src_string) + 1));
            strcpy(substring, src_string);
            substrings[counter] = substring;
            counter += 1;
            break;
        }

        substring = malloc(sizeof(char) * (index_of_found + 1));
        strncpy(substring, src_string, index_of_found);
        substrings[counter] = substring;
        counter += 1;
        src_string = &src_string[index_of_found + 1];
    }

    string_vector r = {
        .data = substrings,
        .len = substrings_len};
    return r;
}
