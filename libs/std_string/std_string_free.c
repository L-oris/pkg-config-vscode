#include <stdlib.h>
#include "std_string.h"

void std_string_free(StdString str)
{
    if (str.data != NULL)
    {
        free(str.data);
    }
}
