cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always \
    -g -ggdb -O2 -DNDEBUG -pedantic-errors \
    -Wall")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(imgui_demo CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Main app
add_executable(myproject)

# sources
target_sources(myproject PRIVATE  src/main.cpp
                                  src/app.cpp src/ui.cpp
                                  src/logic.cpp)

# ImGui core sources
target_sources(
  myproject
  PRIVATE external/imgui/imgui.cpp
          external/imgui/imgui_demo.cpp
          external/imgui/imgui_draw.cpp
          external/imgui/imgui_tables.cpp
          external/imgui/imgui_widgets.cpp)

# ImGui backends (GLFW + OpenGL3)
target_sources(
  myproject PRIVATE  external/imgui/backends/imgui_impl_glfw.cpp
                     external/imgui/backends/imgui_impl_opengl3.cpp)

# Include dirs
target_include_directories(
  myproject PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
                    external/imgui
                    external/imgui/backends)

# Link libs
target_link_libraries(myproject PRIVATE glfw OpenGL::GL)
