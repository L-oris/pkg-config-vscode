#include <stdio.h>
#include "string_utils.h"
#include "app_err.h"
#include "jsn_configs.h"
#include "jsn_root.h"
#include "log.h"
#include "std_string.h"

#define COMMAND_BUFFER_LEN 200
#define STDOUT_BUFFER_LEN 2048

StdString compiler_flags_get_from_pkg_config(char *lib_name, app_err *err)
{
    char command[COMMAND_BUFFER_LEN];
    sprintf(command, "pkg-config --cflags %s", lib_name);
    log_infof("pkg-config command: \"%s\"\n", command);

    FILE *pkg_config_stream = popen(command, "r");
    if (!pkg_config_stream)
    {
        pclose(pkg_config_stream);
        app_err_set(err, INVALID_SHELL_COMMAND, command);
        return std_string_new();
    }

    char stdout_buffer[STDOUT_BUFFER_LEN];
    char *fgets_result = fgets(stdout_buffer, sizeof(char) * STDOUT_BUFFER_LEN, pkg_config_stream);
    pclose(pkg_config_stream);

    if (!fgets_result)
    {
        app_err_set(err, INVALID_LIB_PROVIDED, lib_name);
        return std_string_new();
    }

    return std_string_init(stdout_buffer);
}

static char *strip_prefix(char *compiler_flag)
{
    return string_strip_prefix(compiler_flag, "-I");
}

StringVec compiler_flags_parse(StdString *pkg_config_stdout)
{
    StringVec compiler_flags = string_split(pkg_config_stdout->data, ' ');
    string_vec_map(&compiler_flags, 300, strip_prefix);
    string_vec_map(&compiler_flags, 300, string_rtrim);
    return compiler_flags;
}
