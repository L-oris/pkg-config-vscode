#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <json-c/json.h>

// TODO LORIS: rename typedef to `configs` and vars to `confs`
typedef struct
{
    json_object *jsn;
    int len;
} configurations;

configurations configurations_get(json_object *root);

void configurations_update_include_paths(configurations configs, char *new_values[], int new_values_len);

#endif
