cmake_minimum_required(VERSION 3.22.2)

project(Blaster)

### CXX FLAGS ###
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()


### SOURCES ###

FILE(GLOB SOURCES src/*.cpp)
include_directories(${PROJECT_NAME} src)
add_executable(${PROJECT_NAME} ${SOURCES})
