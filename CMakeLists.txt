cmake_minimum_required(VERSION 3.25)
project(sdl2-audio-poc)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/main.cc
        src/main.h)

# Add SDL2 for window, audio and rendering
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Include audio files
target_include_directories(${PROJECT_NAME} PRIVATE audio)
