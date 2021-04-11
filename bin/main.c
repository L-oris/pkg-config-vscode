#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>
#include "configurations.h"
#include "string_utils.h"

#define PATH_TO_JSON_FILE "../.vscode/c_cpp_properties.json"

#define PKG_CONFIG_COMMAND_BUFFER_LEN 200
#define PKG_CONFIG_STDOUT_BUFFER_LEN 2048

// example program: `libmongoc-1.0`

char *get_compiler_flags_from_pkg_config(char *lib_name)
{
    char command[PKG_CONFIG_COMMAND_BUFFER_LEN];
    sprintf(command, "pkg-config --cflags %s", lib_name);
    // TODO LORIS: redirect stdout to file, and read it in case of error
    printf("DEBUG -- Command: `%s`\n", command);

    FILE *pkg_config_stream = popen(command, "r");
    if (!pkg_config_stream)
    {
        fprintf(stderr, "ERROR -- Failed to execute command `%s`\n", command);
        return NULL;
    }

    char *stdout_buffer = malloc(sizeof(char) * PKG_CONFIG_STDOUT_BUFFER_LEN);
    char *fgets_result = fgets(stdout_buffer, sizeof(char) * PKG_CONFIG_STDOUT_BUFFER_LEN, pkg_config_stream);
    pclose(pkg_config_stream);

    if (!fgets_result)
    {
        fprintf(stderr, "ERROR -- Failed to execute command `%s`\n", command);
        free(stdout_buffer);
        return NULL;
    }

    return stdout_buffer;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "at least one argument required\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        printf("DEBUG -- Iterating lib `%s`\n", argv[i]);
        char *pkg_config_stdout_buffer = get_compiler_flags_from_pkg_config(argv[i]);
        if (!pkg_config_stdout_buffer)
        {
            continue;
        }

        string_vector compiler_flags = string_split(pkg_config_stdout_buffer, ' ');
        // TODO LORIS?: create an iterator that accepts a fn pointer and frees the vector after iteration is done
        for (int j = 0; j < compiler_flags.len; j++)
        {
            char *trimmed_compiler_flag = string_strip_prefix(compiler_flags.data[j], "-I");
            if (trimmed_compiler_flag == NULL)
            {
                fprintf(stderr, "ERROR -- Could not trim compiler flag: %s\n", compiler_flags.data[i]);
                continue;
            }
            printf("DEBUG -- Adding header files: %s\n", trimmed_compiler_flag);
        }

        free(pkg_config_stdout_buffer);
        string_vector_free(compiler_flags);
    }

    return 0;
}

int old_main(void)
{
    json_object *root = json_object_from_file(PATH_TO_JSON_FILE);
    if (!root)
    {
        fprintf(stderr, "ERROR -- %s", json_util_get_last_err());
        return 1;
    }

    struct configurations configs = configurations_get(root);
    configurations_update_include_paths(configs, (char *[]){"hey", "whatsup"}, 2);

    printf("DEBUG -- The updated json file:\n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
    int write_result = json_object_to_file_ext(PATH_TO_JSON_FILE, root, JSON_C_TO_STRING_NOSLASHESCAPE);
    if (write_result == -1)
    {
        fprintf(stderr, "ERROR -- %s", json_util_get_last_err());
        return 1;
    }

    json_object_put(root);
    return 0;
}

// DOCS: https://json-c.github.io/json-c/json-c-0.15/doc/html/json__object_8h.html
// TUTORIAL: https://github.com/rbtylee/tutorial-jsonc/blob/master/tutorial/index.md
