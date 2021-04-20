#pragma once

typedef struct
{
    char *data;
} StdString;

void std_string_free(StdString str);

StdString std_string_new();

StdString std_string_init(char *src);
