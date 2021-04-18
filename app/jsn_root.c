#include <stdio.h>
#include <json-c/json.h>
#include "app_err.h"
#include "jsn_root.h"

void jsn_root_free(JsnRoot jsn_rt)
{
    json_object_put(jsn_rt.jsn);
}

JsnRoot jsn_root_read_from_file(char *path_to_json_file, app_err *err)
{
    JsnRoot jsn_rt = {
        .jsn = NULL,
    };

    json_object *jsn = json_object_from_file(path_to_json_file);
    if (!jsn)
    {
        app_err_set(err, JSON_FAILED_READING, (char *)json_util_get_last_err());
        return jsn_rt;
    }

    jsn_rt.jsn = jsn;
    return jsn_rt;
}

JsnRoot jsn_root_initialize()
{
    json_object *jsn = json_object_new_object();
    json_object_object_add(jsn, "version", json_object_new_int(4));

    JsnRoot jsn_rt = {
        .jsn = jsn,
    };
    return jsn_rt;
}

void jsn_root_print(JsnRoot *jsn_rt)
{
    printf("DEBUG -- The json file:\n\n%s\n", json_object_to_json_string_ext(jsn_rt->jsn, JSON_C_TO_STRING_PRETTY));
}

void jsn_root_write_to_file(JsnRoot *jsn_rt, char *path_to_json_file, app_err *err)
{
    // TODO LORIS: create directory if not exists
    // https://stackoverflow.com/questions/7430248/creating-a-new-directory-in-c
    int write_result = json_object_to_file_ext(path_to_json_file, jsn_rt->jsn, JSON_C_TO_STRING_NOSLASHESCAPE);
    if (write_result == -1)
    {
        app_err_set(err, JSON_FAILED_WRITING, (char *)json_util_get_last_err());
    }
}
