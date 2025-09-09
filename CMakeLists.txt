cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always \
    -g -ggdb -O2 -DNDEBUG -pedantic-errors \
    -Wall")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(imnotator LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)

# #NOTEL DEBUGGING EXECUTABLES
# add_executable(logic src/logic.cpp)
# target_include_directories(
#   logic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
# )

# Main app
add_executable(imnotator)

# sources
target_sources(imnotator PRIVATE  src/main.cpp
                                  src/app.cpp
                                  src/ui.cpp
                                  src/logic.cpp
                                  src/image_loader.cpp
                                  )

# ImGui core sources
target_sources(
  imnotator PRIVATE external/imgui/imgui.cpp
                    external/imgui/imgui_demo.cpp
                    external/imgui/imgui_draw.cpp
                    external/imgui/imgui_tables.cpp
                    external/imgui/imgui_widgets.cpp)

# ImGui backends (GLFW + OpenGL3)
target_sources(
  imnotator PRIVATE external/imgui/backends/imgui_impl_glfw.cpp
                    external/imgui/backends/imgui_impl_opengl3.cpp)

# nativiefiledialog
add_subdirectory(external/nativefiledialog)
target_link_libraries(imnotator PRIVATE nativefiledialog)

# Add glad as a library
add_library(glad STATIC external/glad/src/glad.c)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)
target_include_directories(glad PUBLIC external/glad/include)

# Include dirs
target_include_directories(
  imnotator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
                    external/imgui
                    external/imgui/backends
                    ${OpenCV_INCLUDE_DIRS}
)

# Link libs
target_link_libraries(imnotator PRIVATE glfw OpenGL::GL ${OpenCV_LIBS} glad
                                        dl
                                        nativefiledialog)
