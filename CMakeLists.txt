﻿cmake_minimum_required(VERSION 3.14)
project(RayCaster)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

# Enable compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add executable
add_executable(RayCaster 
    src/main.cpp
    src/render/render.cpp
    src/player/player.cpp
)

# Include headers
target_include_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include/SFML)
target_include_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/src/render)
target_include_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/src/player)
target_include_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/src/utils)
target_include_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/src/font)

# Platform-specific logic
if(WIN32)
    target_link_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include/SFML/libWin)

    target_link_libraries(RayCaster PRIVATE
        $<$<CONFIG:Debug>:sfml-system-d sfml-window-d sfml-graphics-d sfml-audio-d>
        $<$<CONFIG:Release>:sfml-system sfml-window sfml-graphics sfml-audio>
        opengl32
    )

    set_target_properties(RayCaster PROPERTIES WIN32_EXECUTABLE TRUE)

else() # Linux
    target_link_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include/SFML/libLin)

    target_link_libraries(RayCaster PRIVATE
        ${CMAKE_SOURCE_DIR}/include/SFML/libLin/libsfml-graphics.so
        ${CMAKE_SOURCE_DIR}/include/SFML/libLin/libsfml-window.so
        ${CMAKE_SOURCE_DIR}/include/SFML/libLin/libsfml-system.so
        GL
    )
endif()
