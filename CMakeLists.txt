cmake_minimum_required(VERSION 3.28)
project(Project-Capstone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

file( GLOB Src Src/*.cpp)
file( GLOB Include Include/*.hpp)

add_executable(Project-Capstone
        ${SRC}
        ${INCLUDE}
        main.cpp
        Include/graph.hpp
        Include/data_handler.hpp
        Src/graph.cpp
        Src/data_handler.cpp
        Include/simulation.hpp
        Src/simulation.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Users/badre/Desktop/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Users/badre/Desktop/SFML-2.6.1/include)
target_link_libraries(Project-Capstone sfml-system sfml-window sfml-graphics sfml-audio sfml-network)



