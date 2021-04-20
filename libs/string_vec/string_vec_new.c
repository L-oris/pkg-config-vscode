#include <stdlib.h>
#include "string_vec.h"

StringVec string_vec_new()
{
    StringVec string_vec = {
        .data = NULL,
        .len = 0};
    return string_vec;
}
