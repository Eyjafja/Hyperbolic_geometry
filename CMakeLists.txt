cmake_minimum_required(VERSION 3.2)
project(Hyperbolic_geometry)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Ofast")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable (Hyperbolic_geometry src/main.cpp src/project.h)

set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML 2.5 COMPONENTS graphics network audio window system REQUIRED)
target_link_libraries(Hyperbolic_geometry sfml-graphics sfml-audio sfml-network sfml-window sfml-system)