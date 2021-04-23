#include "string_vec.h"

void string_vec_uniq(StringVec *vec)
{
    StringVec new_vec = string_vec_new();
    for (int i = 0; i < vec->len; i++)
    {
        if (!string_vec_includes(&new_vec, vec->data[i]))
        {
            string_vec_push(&new_vec, vec->data[i]);
        }
    }
    string_vec_free(*vec);
    *vec = new_vec;
}
