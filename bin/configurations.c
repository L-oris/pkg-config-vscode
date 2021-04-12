#include <stdio.h>
#include <json-c/json.h>
#include "configurations.h"

configurations configurations_get(json_object *jsn_root)
{
    // TODO LORIS: get rid of this altogether when cases below are refactored
    configurations configs = {
        .jsn = NULL,
        .len = 0};
    json_object *jsn_configs = json_object_object_get(jsn_root, "configurations");
    if (!jsn_configs)
    {
        // TODO LORIS: create a default item instead
        fprintf(stderr, "\"configurations\" field not specified\n");
        return configs;
    }
    int len = json_object_array_length(jsn_configs);
    if (len == 0)
    {
        // TODO LORIS: create a default item instead and update len
        fprintf(stderr, "empty array for configurations\n");
        return configs;
    }

    configs.jsn = jsn_configs;
    configs.len = len;
    return configs;
}

void configurations_update_include_paths(configurations configs, char *new_values[], int new_values_len)
{
    printf("DEBUG -- updating %d configurations\n", configs.len);
    for (int config_idx = 0; config_idx < configs.len; config_idx++)
    {
        json_object *a_config = json_object_array_get_idx(configs.jsn, config_idx);
        json_object *a_config_include_path = json_object_object_get(a_config, "includePath");
        if (!a_config_include_path)
        {
            // TODO LORIS: create a default item instead
            fprintf(stderr, "includePath field not found\n");
            return;
        }

        for (int value_idx = 0; value_idx < new_values_len; value_idx++)
        {
            json_object *new_str = json_object_new_string(new_values[value_idx]);
            json_object_array_add(a_config_include_path, new_str);
        }
    };
}
