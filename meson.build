project('vscode-c-ext', 'c',
  version : '0.1',
  default_options : ['warning_level=3'],
)

subprojects_include_dir = include_directories('subprojects')

cmake = import('cmake')
json_c_proj = cmake.subproject('json-c')
# message('CMake targets for json-c:\n - ' + '\n - '.join(json_c_proj.target_list()))
json_c_dep = json_c_proj.dependency('json-c')

exe = executable('vscode-c-ext', 'main.c',
  dependencies : json_c_dep,
  include_directories : [subprojects_include_dir],
  install : true
)
