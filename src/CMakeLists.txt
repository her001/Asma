cmake_minimum_required (VERSION 2.8)
project (asma)

find_package (PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
add_definitions (${GTK3_CFLAGS_OTHER})

include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})

add_library (addons addons.c)

add_executable (asma asma.c)
target_link_libraries (asma addons ${GTK3_LIBRARIES})
