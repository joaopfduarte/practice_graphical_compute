cmake_minimum_required(VERSION 3.16)
project(graphical_practice)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

include_directories("C:/msys64/mingw64/include")
link_directories("C:/msys64/mingw64/lib")

add_executable(graphical_practice circle.cpp
        graph.cpp
        graph.h)

target_link_libraries(graphical_practice PRIVATE
        OpenGL::GL
        freeglut
        opengl32
        glu32
        winmm
        gdi32
        user32
)
