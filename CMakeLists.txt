cmake_minimum_required(VERSION 3.28)
project(Methodology_finalProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

file( GLOB SRC src/*.cpp)
file( GLOB INCLUDE include/*.hpp)

add_executable(Methodology_finalProject
        ${SRC}
        ${INCLUDE}
        main.cpp
        graph.hpp
        data_handler.hpp
        graph.cpp
        data_handler.cpp
        simulation.hpp
        simulation.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Users/badre/Desktop/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Users/badre/Desktop/SFML-2.6.1/include)
target_link_libraries(Methodology_finalProject sfml-system sfml-window sfml-graphics sfml-audio sfml-network)



