cmake_minimum_required(VERSION 3.12)
project(BodySimulation 
        VERSION  0.1.0
        DESCRIPTION "A simple body simulation project"
        HOMEPAGE_URL "https://github.com/yhxsajmon/Body-simulation"
        LANGUAGES C)

        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

        add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

        include_directories(include)

        set(SOURCES
                src/main.c
                src/Body.c
                src/BodyArray.c
                src/render.c
        )

add_executable(BodySimulation ${SOURCES})
target_link_libraries(BodySimulation m SDL3::SDL3)

target_compile_options(BodySimulation PRIVATE -Wall -Wextra -std=c99)

# Debug configuration
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(BodySimulation PRIVATE DEBUG)
    target_compile_options(BodySimulation PRIVATE -g)
endif()