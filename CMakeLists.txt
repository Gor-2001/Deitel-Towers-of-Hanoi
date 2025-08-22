cmake_minimum_required(VERSION 3.15)

# Project name and language
project(DeitelTowersOfHanoi LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp "towers.cpp" "towers.h")
