cmake_minimum_required(VERSION 3.15)

# Project name and language
project(DeitelTowersOfHanoi LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source and include directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Find all source files in the 'src' directory
file(GLOB_RECURSE SOURCE_FILES
     "${SOURCE_DIR}/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Add the include directory so the compiler can find the headers
target_include_directories(${PROJECT_NAME} PUBLIC
    ${INCLUDE_DIR}
)

# Conditional compilation for ncurses on Linux
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(Curses REQUIRED)
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${CURSES_INCLUDE_DIR}
    )
    target_link_libraries(${PROJECT_NAME} PUBLIC
        ${CURSES_LIBRARIES}
    )
endif()