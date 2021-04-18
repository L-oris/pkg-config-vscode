#pragma once
#include "string_utils.h"
#include "app_err.h"

StringVector compiler_flags_get_from_pkg_config(char *lib_name, app_err *err);

void compiler_flags_parse(StringVector *compiler_flags);

void compiler_flags_write_to_json(StringVector *compiler_flags, app_err *err);
