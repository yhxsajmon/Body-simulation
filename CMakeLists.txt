cmake_minimum_required(VERSION 3.12)
project(BodySimulation 
        VERSION  0.1.0
        DESCRIPTION "A simple body simulation project"
        HOMEPAGE_URL "https://github.com/yhxsajmon/Body-simulation"
        LANGUAGES C)

        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

        add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(BodySimulation main.c Body.c bodyArray.c render.c)
target_link_libraries(BodySimulation m SDL3::SDL3)