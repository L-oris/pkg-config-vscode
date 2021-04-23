#include <stdio.h>
#include <stdbool.h>
#include "app_err.h"
#include "log.h"

static char error_string[2048];

app_err app_err_new()
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
        sprintf(error_string, "invalid shell command: %s\n", msg);
        return;
    case INVALID_LIB_PROVIDED:
        sprintf(error_string, "invalid library provided: %s\n", msg);
        return;
    case FAILED_READING_FROM_JSON_FILE:
        sprintf(error_string, "failed reading from json file: %s\n", msg);
        return;
    case FAILED_WRITING_TO_JSON_FILE:
        sprintf(error_string, "failed writing to json file: %s\n", msg);
        return;
    }
}

void app_err_reset(app_err *err)
{
    app_err_set(err, OK, "");
}

void app_err_print(app_err *err)
{
    log_errorf("%s", error_string);
    app_err_reset(err);
}
