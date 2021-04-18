#pragma once
#include <json-c/json.h>
#include "app_err.h"

typedef struct
{
    json_object *jsn;
} JsnRoot;

void jsn_root_free(JsnRoot jsn_rt);

JsnRoot jsn_root_read_from_file(char *path_to_json_file, app_err *err);

JsnRoot jsn_root_initialize();

void jsn_root_print(JsnRoot *jsn_rt);

void jsn_root_write_to_file(JsnRoot *jsn_rt, char *path_to_json_file, app_err *err);
