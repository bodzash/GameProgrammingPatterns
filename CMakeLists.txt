cmake_minimum_required(VERSION 3.16)

# Project
project(GPG)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Executable
add_executable(
    GPG
    # Source/Command.cpp
    Source/ActorComponent.cpp
)