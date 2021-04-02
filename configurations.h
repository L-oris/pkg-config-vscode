#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <json-c/json.h>

struct configurations
{
    json_object *object;
    int len;
};

struct configurations configurations_get(json_object *root);

void configurations_update_include_paths(struct configurations configs, char *new_values[], int new_values_len);

#endif
