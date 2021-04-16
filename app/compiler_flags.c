#include <stdio.h>
#include "string_utils.h"
#include "app_err.h"
#include "jsn_configs.h"
#include "jsn_root.h"

// TODO LORIS: less verbose
#define PKG_CONFIG_COMMAND_BUFFER_LEN 200
#define PKG_CONFIG_STDOUT_BUFFER_LEN 2048
#define PATH_TO_JSON_FILE "../.vscode/c_cpp_properties.json"

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

static char *strip_prefix(char *compiler_flag)
{
    return string_strip_prefix(compiler_flag, "-I");
}

string_vector compiler_flags_parse(string_vector *compiler_flags)
{
    string_vector_map(compiler_flags, 300, strip_prefix);
    string_vector_map(compiler_flags, 300, string_rtrim);
    return *compiler_flags;
}

void compiler_flags_write_to_json(string_vector *compiler_flags, app_err *err)
{
    jsn_root jsn_rt = jsn_root_read_from_file(PATH_TO_JSON_FILE, err);
    if (*err != OK)
    {
        app_err_reset(err);
        jsn_rt = jsn_root_initialize();
    }

    jsn_configs jsn_confs = jsn_configs_get(&jsn_rt);
    jsn_configs_update_include_paths(jsn_confs, compiler_flags->data, compiler_flags->len);
    jsn_root_print(&jsn_rt);

    jsn_root_write_to_file(&jsn_rt, PATH_TO_JSON_FILE, err);
    jsn_root_free(jsn_rt);
}
