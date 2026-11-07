cmake_minimum_required(VERSION 3.16)
project(QuantumCircuitSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    Eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 5.0.1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Eigen)

add_executable(QuantumCircuitSim
    src/main.cpp
    src/Circuit.cpp
    src/Examples.cpp
)
target_link_libraries(QuantumCircuitSim PRIVATE Eigen3::Eigen)
