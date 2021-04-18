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

string_vector_src = [
    'libs/string_vector/string_vector_free.c',
    'libs/string_vector/string_vector_new.c',
    'libs/string_vector/string_vector_map.c',
]
string_vector = library(
    'string-vector',
    string_vector_src, 
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

libs = [string_utils, string_vector]



# ===========
# Unit Tests
# ===========

string_utils_tests = executable('string-utils-tests',
    sources: 'tests/string_utils_tests.c', 
    link_with : [libs],
    include_directories : libs_include_dir,
)

test('string_utils', string_utils_tests)



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
