project('vscode-c-ext', 'c',
  version : '0.1',
  default_options : ['warning_level=3'],
)

subprojects_include_dir = include_directories('subprojects')

cmake = import('cmake')
json_c_proj = cmake.subproject('json-c')
# message('CMake targets for json-c:\n - ' + '\n - '.join(json_c_proj.target_list()))
json_c_dep = json_c_proj.dependency('json-c')

subdir('libs')

src_exe = [
  'main.c',
  'configurations.c'
]
executable('vscode-c-ext', src_exe,
  dependencies : json_c_dep,
  link_with : [string_utils_lib],
  include_directories : [subprojects_include_dir, libs_include_dir],
  install : true
)

subdir('tests')