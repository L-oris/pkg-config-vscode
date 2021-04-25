project('pkg-config-vscode', 'c',
  version : '0.1',
  default_options : ['warning_level=3'],
)



# ===========
# Subprojects
# ===========

subprojects_include_dir = include_directories('subprojects')

cmake = import('cmake')
json_c_proj = cmake.subproject('json-c')
# message('CMake targets for json-c:\n - ' + '\n - '.join(json_c_proj.target_list()))
json_c_dep = json_c_proj.dependency('json-c')

subprojects = [json_c_dep]



# ===========
# Libs
# ===========

libs_include_dir = include_directories('libs/include')

std_string_src = [
    'libs/std_string/std_string_free.c',
    'libs/std_string/std_string_new.c',
    'libs/std_string/std_string_init.c',
]
std_string = library(
    'std-string',
    std_string_src, 
    include_directories : libs_include_dir,
)

string_vec_src = [
    'libs/string_vec/string_vec_free.c',
    'libs/string_vec/string_vec_new.c',
    'libs/string_vec/string_vec_push.c',
    'libs/string_vec/string_vec_map.c',
    'libs/string_vec/string_vec_concat.c',
    'libs/string_vec/string_vec_print.c',
    'libs/string_vec/string_vec_includes.c',
    'libs/string_vec/string_vec_uniq.c',
]
string_vec = library(
    'string-vec',
    string_vec_src, 
    include_directories : libs_include_dir,
)

string_utils_src = [
    'libs/string_utils/string_rtrim.c',
    'libs/string_utils/string_split.c',
    'libs/string_utils/string_starts_with.c',
    'libs/string_utils/string_strip_prefix.c',
]
string_utils = library(
    'string-utils',
    string_utils_src, 
    include_directories : libs_include_dir,
)

libs = [string_utils, string_vec, std_string]



# ===========
# Unit Tests
# ===========

string_split_tests = executable('string-split-tests',
    sources: 'tests/string_split_tests.c', 
    link_with : [libs],
    include_directories : libs_include_dir,
)
test('string_split', string_split_tests)

string_starts_with_tests = executable('string-starts-with-tests',
    sources: 'tests/string_starts_with_tests.c', 
    link_with : [libs],
    include_directories : libs_include_dir,
)
test('string_starts_with', string_starts_with_tests)

string_strip_prefix_tests = executable('string-strip-prefix-tests',
    sources: 'tests/string_strip_prefix_tests.c', 
    link_with : [libs],
    include_directories : libs_include_dir,
)
test('string_strip_prefix', string_strip_prefix_tests)

string_rtrim_tests = executable('string-rtrim-tests',
    sources: 'tests/string_rtrim_tests.c', 
    link_with : [libs],
    include_directories : libs_include_dir,
)
test('string_rtrim', string_rtrim_tests)

string_vec_push_tests = executable('string-vec-push-tests',
    sources: 'tests/string_vec_push_tests.c', 
    link_with : [libs],
    include_directories : libs_include_dir,
)

test('string_vec_push', string_vec_push_tests)

string_vec_concat_tests = executable('string-vec-concat-tests',
    sources: 'tests/string_vec_concat_tests.c', 
    link_with : [libs],
    include_directories : libs_include_dir,
)
test('string_vec_concat', string_vec_concat_tests)

string_vec_includes_tests = executable('string-vec-includes-tests',
    sources: 'tests/string_vec_includes_tests.c', 
    link_with : [libs],
    include_directories : libs_include_dir,
)
test('string_vec_includes', string_vec_includes_tests)

string_vec_uniq_tests = executable('string-vec-uniq-tests',
    sources: 'tests/string_vec_uniq_tests.c', 
    link_with : [libs],
    include_directories : libs_include_dir,
)
test('string_vec_uniq', string_vec_uniq_tests)



# ===========
# Executable
# ===========

app_include_dir = include_directories('app/include')

app_src = [
  'app/app_err.c',
  'app/compiler_flags.c',
  'app/jsn_configs.c',
  'app/jsn_root.c',
  'app/main.c',
]
executable('pkg-config-vscode', app_src,
  dependencies : subprojects,
  link_with : libs,
  include_directories : [subprojects_include_dir, libs_include_dir, app_include_dir],
  install : true
)
