#include <stdio.h>
#include <string.h>
#include "app_err.h"
#include "compiler_flags.h"
#include "jsn_root.h"
#include "jsn_configs.h"
#include "log.h"
#include "std_string.h"
#include "string_vec.h"

// example program: `libmongoc-1.0`

static void parse_args(int argc, char *argv[], app_err *err);
static void print_help();

int main(int argc, char *argv[])
{
    app_err err = app_err_new();

    parse_args(argc, argv, &err);
    if (app_err_happened(&err))
    {
        if (err == NOT_ENOUGH_ARGUMENTS)
        {
            app_err_print();
        }
        print_help();
        return 1;
    }

    StringVec compiler_flags = string_vec_new();
    for (int i = 1; i < argc; i++)
    {
        log_infof("iterating lib \"%s\"\n", argv[i]);
        StdString pkg_config_stdout = compiler_flags_get_from_pkg_config(argv[i], &err);
        if (app_err_happened(&err))
        {
            app_err_print(&err);
        }
        else
        {
            StringVec new_compiler_flags = compiler_flags_parse(&pkg_config_stdout);
            string_vec_concat(&compiler_flags, new_compiler_flags);
        }
        std_string_free(pkg_config_stdout);
    }
    if (compiler_flags.len == 0)
    {
        string_vec_free(compiler_flags);
        return 0;
    }
    string_vec_uniq(&compiler_flags);
    log_infof("collected %d compiler flags\n", compiler_flags.len);

    JsnRoot jsn_rt = jsn_root_get();
    jsn_configs jsn_confs = jsn_configs_get(&jsn_rt);
    jsn_configs_update_compiler_flags(jsn_confs, &compiler_flags);
    jsn_root_write_to_file(&jsn_rt, &err);
    jsn_root_free(jsn_rt);
    string_vec_free(compiler_flags);

    if (app_err_happened(&err))
    {
        app_err_print(&err);
        return 1;
    }
    log_successf("%s", "json file updated\n");
    return 0;
}

static void parse_args(int argc, char *argv[], app_err *err)
{
    if (argc < 2)
    {
        app_err_set(err, NOT_ENOUGH_ARGUMENTS, "");
        return;
    }
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        app_err_set(err, HELP_FLAG, "");
        return;
    }
}

static void print_help()
{
    printf("\nUSAGE:\n"
           "\tpkg-config-vscode [FLAGS] [LIB]...\n"
           "\nARGS:\n"
           "\t<LIB>...         Libraries to search include paths for\n"
           "\nFLAGS:\n"
           "\t-h, --help       Prints help information\n"
           "\n");
}

// DOCS: https://json-c.github.io/json-c/json-c-0.15/doc/html/json__object_8h.html
// TUTORIAL: https://github.com/rbtylee/tutorial-jsonc/blob/master/tutorial/index.md
