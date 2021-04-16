#include <stdio.h>
#include <stdbool.h>
#include "app_err.h"

static char error_string[2048];

app_err app_err_init()
{
    return OK;
}

bool app_err_happened(app_err *err)
{
    return *err != OK;
}

void app_err_set(app_err *err, app_err new_value, char *msg)
{
    *err = new_value;
    switch (new_value)
    {
    case OK:
        sprintf(error_string, "");
        return;
    case INVALID_SHELL_COMMAND:
        sprintf(error_string, "Invalid shell command: %s\n", msg);
        return;
    case INVALID_LIB_PROVIDED:
        sprintf(error_string, "Invalid library provided: %s\n", msg);
        return;
    case JSON_FAILED_READING:
        sprintf(error_string, "Failed to read json file: %s\n", msg);
        return;
    case JSON_FAILED_WRITING:
        sprintf(error_string, "Failed to write json file: %s\n", msg);
        return;
    }
}

void app_err_reset(app_err *err)
{
    app_err_set(err, OK, "");
}

// TODO LORIS?: more beautiful logging library
void app_err_print(app_err *err)
{
    fprintf(stderr, "ERROR -- %s", error_string);
    app_err_set(err, OK, "");
}
