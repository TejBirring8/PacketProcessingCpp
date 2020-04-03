cmake_minimum_required(VERSION 3.14)
project(CodeTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(CodeTest
        compile_options.h
        main.cpp
        state_machine/state_machine.cpp
        app/app_debug_functions.cpp
        app/app_ui_functions.cpp
        app/app_error_handling_functions.cpp
        )