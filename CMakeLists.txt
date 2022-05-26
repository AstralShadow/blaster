cmake_minimum_required(VERSION 3.22.2)

project(Blaster VERSION 1.0)


### SOURCES ###

FILE(GLOB SOURCES src/*.cpp)
include_directories(${PROJECT_NAME} src)
add_executable(${PROJECT_NAME} ${SOURCES})


### CONFIGURATION ###

configure_file(src/version.hpp.in src/version.hpp)
target_include_directories( ${PROJECT_NAME}
    PUBLIC "${PROJECT_BINARY_DIR}/src"
)


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


### DEPENDENCIES ###

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})



