#pragma once
#include <stdbool.h>
#include "string_vector.h"

// Splits the strings into tokens.
// If no delimiter is found, the vector will contain a single element.
StringVector string_split(char *src_string, char delimiter);

bool string_starts_with(char *src_string, char *prefix);

// If the source string doesn't start with prefix, a NULL pointer is returned.
// Otherwise, the returned pointer points to the source string, but is shifted prefix_len characters.
char *string_strip_prefix(char *src_string, char *prefix);

// The function modifies str, so constant strings are going to crash the program.
// If there are no characters to be trimmed, the str param is simply returned as is.
char *string_rtrim(char *str);
