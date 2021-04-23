#pragma once
#include <json-c/json.h>
#include "app_err.h"
#include "jsn_root.h"
#include "string_vec.h"

typedef struct
{
    json_object *jsn;
    int len;
} jsn_configs;

jsn_configs jsn_configs_get(JsnRoot *jsn_rt);

void jsn_configs_update_compiler_flags(jsn_configs jsn_confs, StringVec *new_compiler_flags);
