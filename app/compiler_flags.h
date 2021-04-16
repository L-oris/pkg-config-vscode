#pragma once
#include "string_utils.h"
#include "app_err.h"

string_vector compiler_flags_get_from_pkg_config(char *lib_name, app_err *err);

string_vector compiler_flags_parse(string_vector *compiler_flags);

void compiler_flags_write_to_json(string_vector *compiler_flags, app_err *err);
