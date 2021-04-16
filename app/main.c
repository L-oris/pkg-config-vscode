#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "configurations.h"
#include "string_utils.h"
#include "app_err.h"

#define PATH_TO_JSON_FILE "../.vscode/c_cpp_properties.json"

#define PKG_CONFIG_COMMAND_BUFFER_LEN 200
#define PKG_CONFIG_STDOUT_BUFFER_LEN 2048

// example program: `libmongoc-1.0`

// TODO LORIS: use references to indicate ownership and who should free

json_object *jsn_root_read_from_file(char *path_to_json_file, app_err *err)
{
    json_object *jsn_root = json_object_from_file(path_to_json_file);
    if (!jsn_root)
    {
        app_err_set(err, JSON_FAILED_READING, (char *)json_util_get_last_err());
        return NULL;
    }
    return jsn_root;
}

json_object *jsn_root_initialize()
{
    json_object *jsn_root = json_object_new_object();
    json_object_object_add(jsn_root, "version", json_object_new_int(4));
    return jsn_root;
}

void jsn_root_print(json_object *jsn_root)
{
    printf("DEBUG -- The json file:\n\n%s\n", json_object_to_json_string_ext(jsn_root, JSON_C_TO_STRING_PRETTY));
}

void jsn_root_write_to_file(json_object *jsn_root, char *path_to_json_file, app_err *err)
{
    // TODO LORIS: create directory if not exists
    // https://stackoverflow.com/questions/7430248/creating-a-new-directory-in-c
    int write_result = json_object_to_file_ext(path_to_json_file, jsn_root, JSON_C_TO_STRING_NOSLASHESCAPE);
    if (write_result == -1)
    {
        app_err_set(err, JSON_FAILED_WRITING, (char *)json_util_get_last_err());
    }
}

string_vector compiler_flags_get_from_pkg_config(char *lib_name, app_err *err)
{
    char command[PKG_CONFIG_COMMAND_BUFFER_LEN];
    sprintf(command, "pkg-config --cflags %s", lib_name);
    // TODO LORIS: redirect stdout to file, and read it in case of error
    printf("DEBUG -- Command: `%s`\n", command);

    FILE *pkg_config_stream = popen(command, "r");
    if (!pkg_config_stream)
    {
        pclose(pkg_config_stream);
        app_err_set(err, INVALID_SHELL_COMMAND, command);
        return string_vector_empty();
    }

    char stdout_buffer[PKG_CONFIG_STDOUT_BUFFER_LEN];
    char *fgets_result = fgets(stdout_buffer, sizeof(char) * PKG_CONFIG_STDOUT_BUFFER_LEN, pkg_config_stream);
    pclose(pkg_config_stream);

    if (!fgets_result)
    {
        app_err_set(err, INVALID_LIB_PROVIDED, lib_name);
        return string_vector_empty();
    }

    return string_split(stdout_buffer, ' ');
}

char *compiler_flag_strip_prefix(char *compiler_flag)
{
    return string_strip_prefix(compiler_flag, "-I");
}

string_vector compiler_flags_parse(string_vector *compiler_flags)
{
    string_vector_map(compiler_flags, 300, compiler_flag_strip_prefix);
    string_vector_map(compiler_flags, 300, string_rtrim);
    return *compiler_flags;
}

void compiler_flags_write_to_json(string_vector *compiler_flags, app_err *err)
{
    json_object *jsn_root = jsn_root_read_from_file(PATH_TO_JSON_FILE, err);
    if (*err != OK)
    {
        app_err_reset(err);
        jsn_root = jsn_root_initialize();
    }

    configurations configs = configurations_get(jsn_root);
    configurations_update_include_paths(configs, (*compiler_flags).data, (*compiler_flags).len);
    jsn_root_print(jsn_root);

    jsn_root_write_to_file(jsn_root, PATH_TO_JSON_FILE, err);
    json_object_put(jsn_root);
}

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
        printf("DEBUG -- Iterating lib `%s`\n", argv[i]);
        string_vector compiler_flags = compiler_flags_get_from_pkg_config(argv[i], &err);
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
