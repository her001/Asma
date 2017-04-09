cmake_minimum_required (VERSION 2.8)
project (asma)

# GTK 3
find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)
add_definitions (${GTK3_CFLAGS_OTHER})
include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})

# ASMA files
add_library (addons addons.c errors errors.c settings settings.c)
add_executable (asma asma.c)
target_link_libraries (asma addons ${GTK3_LIBRARIES})

# Installation
install (TARGETS asma DESTINATION bin)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.desktop
	DESTINATION applications)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.png
	DESTINATION icons/hicolor/256x256)
