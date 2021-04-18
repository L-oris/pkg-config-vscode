#include <stdio.h>
#include <json-c/json.h>
#include "jsn_configs.h"
#include "app_err.h"
#include "jsn_root.h"

jsn_configs jsn_configs_get(JsnRoot *jsn_rt)
{
    json_object *jsn_confs = json_object_object_get(jsn_rt->jsn, "configurations");
    if (!jsn_confs)
    {
        jsn_confs = json_object_new_array();
        json_object_object_add(jsn_rt->jsn, "configurations", jsn_confs);
    }

    int configs_len = json_object_array_length(jsn_confs);
    if (configs_len == 0)
    {
        json_object *a_config = json_object_new_object();
        json_object_object_add(a_config, "name", json_object_new_string("default"));
        json_object_array_add(jsn_confs, a_config);
        configs_len += 1;
    }

    jsn_configs confs = {
        .jsn = jsn_confs,
        .len = configs_len};
    return confs;
}

void jsn_configs_update_include_paths(jsn_configs jsn_confs, char *new_values[], int new_values_len)
{
    printf("DEBUG -- updating %d configurations\n", jsn_confs.len);
    for (int config_idx = 0; config_idx < jsn_confs.len; config_idx++)
    {
        json_object *a_config = json_object_array_get_idx(jsn_confs.jsn, config_idx);
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
