#pragma once
#include <stdbool.h>

typedef enum
{
    OK,
    HELP_FLAG,
    NOT_ENOUGH_ARGUMENTS,
    INVALID_PKG_CONFIG_COMMAND,
    INVALID_LIB_PROVIDED,
    FAILED_READING_FROM_JSON_FILE,
    FAILED_WRITING_TO_JSON_FILE,
} app_err;

app_err app_err_new();

bool app_err_happened(app_err *err);

void app_err_set(app_err *err, app_err new_value, char *msg);

void app_err_reset(app_err *err);

void app_err_print();

#define CHECK_APP_ERR_OR_RETURN(x) \
    {                              \
        if (*err != OK)            \
        {                          \
            return x;              \
        }                          \
    }
