cmake_minimum_required(VERSION 3.16)
project(PrimeRoot)

set(CMAKE_CXX_STANDARD 14)
# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)
find_package(OpenMP REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(PrimeRoot main.cpp
        src/Step_Functions.cpp
        include/Step_Functions.h
        src/Memory_Functions.cpp
        include/Memory_Functions.h
        src/Iterator_Functions.cpp
        include/Iterator_Functions.h)

target_link_libraries(${PROJECT_NAME}
        "/usr/lib/x86_64-linux-gnu/libgmp.a"
        "/usr/lib/x86_64-linux-gnu/libgmpxx.a"
        )

