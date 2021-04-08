#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>
#include "configurations.h"

#define PATH_TO_JSON_FILE "../.vscode/c_cpp_properties.json"

// example program: `libmongoc-1.0`

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "one argument required\n");
        return 1;
    }
    char command_buffer[100];
    sprintf(command_buffer, "pkg-config --cflags %s", argv[1]);
    printf("DEBUG -- %s\n", command_buffer);

    FILE *pkg_config_file = popen(command_buffer, "r");
    if (!pkg_config_file)
    {
        fprintf(stderr, "Failed to execute command `%s`\n", command_buffer);
        return 1;
    }

    // TODO LORIS: allow writing as much as you can in dynamically allocated string?
    char pkg_config_stdout[2048];
    fgets(pkg_config_stdout, sizeof(pkg_config_stdout), pkg_config_file);
    printf("Successful:\n%s\n", pkg_config_stdout);

    pclose(pkg_config_file);
    return 0;
}

int old_main(void)
{
    json_object *root = json_object_from_file(PATH_TO_JSON_FILE);
    if (!root)
    {
        fprintf(stderr, "%s", json_util_get_last_err());
        return 1;
    }

    struct configurations configs = configurations_get(root);
    configurations_update_include_paths(configs, (char *[]){"hey", "whatsup"}, 2);

    printf("DEBUG -- The updated json file:\n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
    int write_result = json_object_to_file_ext(PATH_TO_JSON_FILE, root, JSON_C_TO_STRING_NOSLASHESCAPE);
    if (write_result == -1)
    {
        fprintf(stderr, "%s", json_util_get_last_err());
        return 1;
    }

    json_object_put(root);
    return 0;
}

// DOCS: https://json-c.github.io/json-c/json-c-0.15/doc/html/json__object_8h.html
// TUTORIAL: https://github.com/rbtylee/tutorial-jsonc/blob/master/tutorial/index.md
