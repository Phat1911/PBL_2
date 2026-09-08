cmake_minimum_required(VERSION 3.16)
project(Qt6Demo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Qt6Demo
    main.cpp
)

target_link_libraries(Qt6Demo PRIVATE Qt6::Widgets)

if(WIN32)
    set_target_properties(Qt6Demo PROPERTIES
        WIN32_EXECUTABLE ON
    )
endif()
