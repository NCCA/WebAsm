cmake_minimum_required(VERSION 3.2)

add_definitions("-std=c++11 ")
set(CMAKE_CXX_COMPILER /Users/jmacey/emsdk/fastcomp/emscripten/em++)
set(CMAKE_CXX_FLAGS "-s WASM=1 -s USE_SDL=2 -O3")
project(SequenceBlock)
file(GLOB sources *.cpp)
add_executable(index.js ${sources})