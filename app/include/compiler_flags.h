#pragma once
#include "std_string.h"
#include "string_vec.h"
#include "app_err.h"

StdString compiler_flags_get_from_pkg_config(char *lib_name, app_err *err);

StringVec compiler_flags_parse(StdString *pkg_config_stdout);
