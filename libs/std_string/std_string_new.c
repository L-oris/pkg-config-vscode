#include <stdlib.h>
#include "std_string.h"

StdString std_string_new()
{
    StdString str = {
        .data = NULL,
    };
    return str;
}
