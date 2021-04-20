#include <stdio.h>
#include "app_err.h"
#include "compiler_flags.h"
#include "string_utils.h"
#include "log.h"
#include "jsn_root.h"
#include "jsn_configs.h"
#include "std_string.h"
#include "string_vec.h"

#define PATH_TO_JSON_FILE "../.vscode/c_cpp_properties.json"

// example program: `libmongoc-1.0`

int main(int argc, char *argv[])
{
    app_err err = app_err_new();
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
        log_infof("%s", "no compiler flags to be written, exiting earlier\n");
        string_vec_free(compiler_flags);
        return 0;
    }

    JsnRoot jsn_rt = jsn_root_get(PATH_TO_JSON_FILE);
    jsn_configs jsn_confs = jsn_configs_get(&jsn_rt);
    jsn_configs_update_include_paths(jsn_confs, compiler_flags.data, compiler_flags.len);
    jsn_root_write_to_file(&jsn_rt, PATH_TO_JSON_FILE, &err);
    jsn_root_free(jsn_rt);
    string_vec_free(compiler_flags);

    if (app_err_happened(&err))
    {
        app_err_print(&err);
        return 1;
    }
    return 0;
}

// DOCS: https://json-c.github.io/json-c/json-c-0.15/doc/html/json__object_8h.html
// TUTORIAL: https://github.com/rbtylee/tutorial-jsonc/blob/master/tutorial/index.md
