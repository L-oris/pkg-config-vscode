#pragma once
#include <stdio.h>

#define ANSI_COLOR_GREEN "\033[1;32m"
#define ANSI_COLOR_BLUE "\033[1;34m"
#define ANSI_COLOR_YELLOW "\033[1;33m"
#define ANSI_COLOR_RED "\033[1;31m"
#define ANSI_COLOR_RESET "\033[0m"

#define log_debugf(format, ...) \
    printf("%sDebug:%s %s:%d => " format, ANSI_COLOR_GREEN, ANSI_COLOR_RESET, __FILE__, __LINE__, __VA_ARGS__)

#define log_infof(format, ...) \
    printf("%sInfo:%s " format, ANSI_COLOR_BLUE, ANSI_COLOR_RESET, __VA_ARGS__)

#define log_warnf(format, ...) \
    printf("%sWarn:%s " format, ANSI_COLOR_YELLOW, ANSI_COLOR_RESET, __VA_ARGS__)

#define log_errorf(format, ...) \
    fprintf(stderr, "%sError:%s " format, ANSI_COLOR_RED, ANSI_COLOR_RESET, __VA_ARGS__)

#define log_successf(format, ...) \
    fprintf(stderr, "%sSuccess:%s " format, ANSI_COLOR_GREEN, ANSI_COLOR_RESET, __VA_ARGS__)
