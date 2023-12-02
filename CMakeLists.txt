#cmake -G "Visual Studio 17 2022" -A x64
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(warning_condenser)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(warning_condenser
  "warning_condenser.cpp"
)

