cmake_minimum_required(VERSION 3.6)
project(engine2d)

set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
include_directories(${SDL2_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(SOURCE_FILES src/main.cpp src/Vec.cpp src/Vec.hpp src/Poly.cpp src/Poly.hpp src/Render.cpp src/Render.hpp src/Consts.hpp src/Line.cpp src/Line.hpp src/Time.cpp src/Time.h src/Input.cpp src/Input.h)
add_library(engine2d_main ${SOURCE_FILES})
add_executable(engine2d ${SOURCE_FILES} src/Seg.cpp src/Seg.hpp src/PhysicsObject.cpp src/PhysicsObject.h src/World.cpp src/World.hpp src/Collision.cpp src/Collision.hpp)
target_link_libraries(engine2d ${SDL2_LIBRARY})

add_subdirectory(lib/gtest-1.8.0/googletest)
add_subdirectory(test)
include_directories(lib/gtest-1.8.0/googletest/include)
