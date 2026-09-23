cmake_minimum_required(VERSION 3.20)

project(WoSFluidSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(SPH2D_test
    src/Tests/SPH2D_test.cpp
    src/Rendering/rendering2D.cpp
    src/Solutions/SPH2D.cpp
    src/Simulation/ParticleSpawner.cpp
)

target_include_directories(SPH2D_test PRIVATE
    src
)

target_link_libraries(SPH2D_test PRIVATE
    raylib
)