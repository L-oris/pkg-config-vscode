#pragma once
#include <json-c/json.h>
#include "app_err.h"

typedef struct
{
    json_object *jsn;
} JsnRoot;

void jsn_root_free(JsnRoot jsn_rt);

JsnRoot jsn_root_get();

void jsn_root_print(JsnRoot *jsn_rt);

void jsn_root_write_to_file(JsnRoot *jsn_rt, app_err *err);
