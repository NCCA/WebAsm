cmake_minimum_required(VERSION 3.2)

add_definitions("-std=c++11 ")
set(CMAKE_CXX_COMPILER em++)
set(CMAKE_CXX_FLAGS " -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1  -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1  -O3")
project(Iteration)
file(GLOB sources src/*.cpp include/*.h)
include_directories(include /usr/local/include)
add_executable(index.js ${sources})
