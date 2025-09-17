cmake_minimum_required(VERSION 3.12)
project(BodySimulation 
        VERSION  0.1.0
        DESCRIPTION "A simple body simulation project"
        HOMEPAGE_URL "https://github.com/yhxsajmon/Body-simulation"
        LANGUAGES C)
add_executable(BodySimulation main.c Body.c render.c)
target_link_libraries(BodySimulation m)