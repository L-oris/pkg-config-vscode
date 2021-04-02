#include <stdio.h>
#include <json-c/json.h>
#include "configurations.h"

struct configurations configurations_get(json_object *root)
{
    // TODO LORIS: get rid of this altogether when cases below are refactored
    struct configurations ret = {
        .object = NULL,
        .len = 0};
    json_object *object = json_object_object_get(root, "configurations");
    if (!object)
    {
        // TODO LORIS: create a default item instead
        fprintf(stderr, "\"configurations\" field not specified\n");
        return ret;
    }
    int len = json_object_array_length(object);
    if (len == 0)
    {
        // TODO LORIS: create a default item instead and update len
        fprintf(stderr, "empty array for configurations\n");
        return ret;
    }

    ret.object = object;
    ret.len = len;
    return ret;
}

void configurations_update_include_paths(struct configurations configs, char *new_values[], int new_values_len)
{
    printf("DEBUG -- updating %d configurations\n", configs.len);
    for (int config_idx = 0; config_idx < configs.len; config_idx++)
    {
        json_object *a_configuration = json_object_array_get_idx(configs.object, config_idx);
        json_object *a_configuration_include_path = json_object_object_get(a_configuration, "includePath");
        if (!a_configuration_include_path)
        {
            // TODO LORIS: create a default item instead
            fprintf(stderr, "includePath field not found\n");
            return;
        }

        for (int value_idx = 0; value_idx < new_values_len; value_idx++)
        {
            json_object *new_str = json_object_new_string(new_values[value_idx]);
            json_object_array_add(a_configuration_include_path, new_str);
        }
    };
}
