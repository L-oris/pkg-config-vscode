libs_include_dir = include_directories('include')

string_utils_src = [
    'string/string_split.c',
    'string/string_starts_with.c',
    'string/string_strip_prefix.c',
    'string/string_vector.c',
]
string_utils_lib = library(
    'string_utils',
    string_utils_src, 
    include_directories : libs_include_dir,
)