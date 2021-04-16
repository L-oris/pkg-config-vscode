#include <stdio.h>
#include <json-c/json.h>
#include "configurations.h"
#include "app_err.h"

configurations configurations_get(json_object *jsn_root)
{
    json_object *jsn_configs = json_object_object_get(jsn_root, "configurations");
    if (!jsn_configs)
    {
        jsn_configs = json_object_new_array();
        json_object_object_add(jsn_root, "configurations", jsn_configs);
    }

    int configs_len = json_object_array_length(jsn_configs);
    if (configs_len == 0)
    {
        json_object *a_config = json_object_new_object();
        json_object_object_add(a_config, "name", json_object_new_string("default"));
        json_object_array_add(jsn_configs, a_config);
        configs_len += 1;
    }

    configurations configs = {
        .jsn = jsn_configs,
        .len = configs_len};
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
            a_config_include_path = json_object_new_array();
            json_object_array_add(a_config_include_path, json_object_new_string("${workspaceFolder}/**"));
            json_object_object_add(a_config, "includePath", a_config_include_path);
            // TODO LORIS: log::debug
        }

        for (int value_idx = 0; value_idx < new_values_len; value_idx++)
        {
            json_object *new_str = json_object_new_string(new_values[value_idx]);
            json_object_array_add(a_config_include_path, new_str);
        }
    };
}
