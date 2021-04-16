#pragma once
#include <json-c/json.h>
#include "app_err.h"

typedef struct
{
    json_object *jsn;
} jsn_root;

jsn_root jsn_root_read_from_file(char *path_to_json_file, app_err *err);

jsn_root jsn_root_initialize();

void jsn_root_print(jsn_root *jsn_rt);

void jsn_root_write_to_file(jsn_root *jsn_rt, char *path_to_json_file, app_err *err);

void jsn_root_free(jsn_root jsn_rt);
