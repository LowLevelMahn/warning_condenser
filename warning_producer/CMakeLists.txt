#cmake -G "Visual Studio 17 2022" -A x64
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(warning_producer)

add_executable(warning_producer
  "warning_producer.cpp"
)

if(MSVC)
  target_compile_options(warning_producer PRIVATE /W4)
else()
  target_compile_options(warning_producer PRIVATE -Wall -Wextra -Wpedantic)
endif()

