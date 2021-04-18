#include <stdio.h>
#include "app_err.h"
#include "compiler_flags.h"
#include "string_utils.h"

// example program: `libmongoc-1.0`

int main(int argc, char *argv[])
{
    app_err err = app_err_init();

    // TODO LORIS: lib for parsing cli args
    if (argc < 2)
    {
        fprintf(stderr, "at least one argument required\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        // TODO LORIS: fn parse_lib
        // TODO LORIS: merge multiple compiler_flag_vectors together before writing to file
        printf("DEBUG -- Iterating lib `%s`\n", argv[i]);
        StringVector compiler_flags = compiler_flags_get_from_pkg_config(argv[i], &err);
        if (app_err_happened(&err))
        {
            app_err_print(&err);
            continue;
        }
        compiler_flags_parse(&compiler_flags);

        compiler_flags_write_to_json(&compiler_flags, &err);
        if (app_err_happened(&err))
        {
            app_err_print(&err);
        }

        string_vector_free(compiler_flags);
    }

    return 0;
}

// DOCS: https://json-c.github.io/json-c/json-c-0.15/doc/html/json__object_8h.html
// TUTORIAL: https://github.com/rbtylee/tutorial-jsonc/blob/master/tutorial/index.md
