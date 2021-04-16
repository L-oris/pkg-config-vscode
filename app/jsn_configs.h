#pragma once
#include <json-c/json.h>
#include "app_err.h"
#include "jsn_root.h"

typedef struct
{
    json_object *jsn;
    int len;
} jsn_configs;

jsn_configs jsn_configs_get(jsn_root *jsn_rt);

void jsn_configs_update_include_paths(jsn_configs jsn_confs, char *new_values[], int new_values_len);
