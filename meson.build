project('vscode-c-ext', 'c',
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

string_utils_src = [
    'libs/string/string_split.c',
    'libs/string/string_starts_with.c',
    'libs/string/string_strip_prefix.c',
    'libs/string/string_vector.c',
]
string_utils = library(
    'string_utils',
    string_utils_src, 
    include_directories : libs_include_dir,
)

libs = [string_utils]



# ===========
# Unit Tests
# ===========

string_utils_tests = executable('string_tests',
    sources: 'tests/string_tests.c', 
    link_with : [libs],
    include_directories : libs_include_dir,
)

test('string_utils', string_utils_tests)



# ===========
# Executable
# ===========

bin_src = [
  'bin/main.c',
  'bin/configurations.c'
]
executable('add-vscode-header-files', bin_src,
  dependencies : subprojects,
  link_with : libs,
  include_directories : [subprojects_include_dir, libs_include_dir],
  install : true
)
