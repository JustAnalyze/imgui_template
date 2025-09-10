cmake_minimum_required(VERSION 3.10)
project(nativefiledialog_patch C)

set(CMAKE_C_STANDARD 99)

set(NFD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/nativefiledialog)

add_library(nativefiledialog
    ${NFD_DIR}/src/nfd_common.c
)

if (WIN32)
    target_sources(nativefiledialog PRIVATE ${NFD_DIR}/src/nfd_win.c)

elseif (APPLE)
    target_sources(nativefiledialog PRIVATE ${NFD_DIR}/src/nfd_cocoa.m)

elseif (UNIX)
    target_sources(nativefiledialog PRIVATE ${NFD_DIR}/src/nfd_gtk.c)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

    target_include_directories(nativefiledialog PRIVATE ${GTK3_INCLUDE_DIRS})
    target_link_libraries(nativefiledialog PRIVATE ${GTK3_LIBRARIES})
    add_definitions(${GTK3_CFLAGS_OTHER})
endif()

target_include_directories(nativefiledialog PUBLIC
    ${NFD_DIR}/src/include
)
