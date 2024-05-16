cmake_minimum_required(VERSION 2.6.0)
project(particle_simulation)

# Set the path to SDL2
set(SDL2_INCLUDE_DIR "SDL2/include")
set(SDL2_LIBRARY_DIR "SDL2/lib")

include_directories(${SDL2_INCLUDE_DIR})
# Prevents CMake from being confused by non-absolute paths
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/${SDL2_LIBRARY_DIR})

add_executable(particle_simulation main.c)
target_link_libraries(particle_simulation mingw32 SDL2main SDL2)
