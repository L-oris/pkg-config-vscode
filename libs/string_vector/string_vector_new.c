#include <stdlib.h>
#include "string_vector.h"

StringVector string_vector_new()
{
    StringVector string_vec = {
        .data = NULL,
        .len = 0};
    return string_vec;
}
