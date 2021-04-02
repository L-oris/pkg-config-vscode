#include <stdio.h>
#include <json-c/json.h>
#include "configurations.h"

#define PATH_TO_JSON_FILE "../.vscode/c_cpp_properties.json"

int main(void)
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
