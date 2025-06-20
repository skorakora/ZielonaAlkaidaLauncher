cmake_minimum_required(VERSION 3.15)
project(MinecraftLauncher)

set(CMAKE_CXX_STANDARD 17)

# GLFW i ImGui jako submoduły
add_subdirectory(extern/glfw)

# IMGUI nie ma CMake, konfigurujemy go ręcznie
file(GLOB IMGUI_SRC
    extern/imgui/*.cpp
    extern/imgui/backends/imgui_impl_glfw.cpp
    extern/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
    extern/imgui
    extern/imgui/backends
)
target_link_libraries(imgui PUBLIC glfw)

# Główna aplikacja
add_executable(MinecraftLauncher main.cpp)
target_include_directories(MinecraftLauncher PRIVATE
    extern/imgui
    extern/imgui/backends
)
target_link_libraries(MinecraftLauncher PRIVATE
    glfw
    imgui
    opengl32
)
