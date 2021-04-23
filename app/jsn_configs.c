#include <stdio.h>
#include <json-c/json.h>
#include "jsn_configs.h"
#include "app_err.h"
#include "jsn_root.h"
#include "log.h"
#include "string_vec.h"

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

StringVec get_current_compiler_flags_from_a_config_include_path(json_object *a_config_include_path)
{
    StringVec flags = string_vec_new();
    int include_path_len = json_object_array_length(a_config_include_path);
    for (int i = 0; i < include_path_len; i++)
    {
        json_object *a_jsn_flag = json_object_array_get_idx(a_config_include_path, i);
        const char *a_flag = json_object_get_string(a_jsn_flag);
        string_vec_push(&flags, (char *)a_flag);
    }
    return flags;
}

void jsn_configs_update_compiler_flags(jsn_configs jsn_confs, StringVec *new_compiler_flags)
{
    log_infof("updating %d configuration(s)\n", jsn_confs.len);
    for (int config_idx = 0; config_idx < jsn_confs.len; config_idx++)
    {
        json_object *a_config = json_object_array_get_idx(jsn_confs.jsn, config_idx);
        json_object *a_config_include_path = json_object_object_get(a_config, "includePath");
        if (!a_config_include_path)
        {
            a_config_include_path = json_object_new_array();
            json_object_array_add(a_config_include_path, json_object_new_string("${workspaceFolder}/**"));
            json_object_object_add(a_config, "includePath", a_config_include_path);
        }

        StringVec current_compiler_flags = get_current_compiler_flags_from_a_config_include_path(a_config_include_path);

        for (int flag_idx = 0; flag_idx < new_compiler_flags->len; flag_idx++)
        {
            char *a_new_compiler_flag = new_compiler_flags->data[flag_idx];
            if (!string_vec_includes(&current_compiler_flags, a_new_compiler_flag))
            {
                json_object *a_jsn_compiler_flag = json_object_new_string(new_compiler_flags->data[flag_idx]);
                json_object_array_add(a_config_include_path, a_jsn_compiler_flag);
            }
        }
        string_vec_free(current_compiler_flags);
    };
}
