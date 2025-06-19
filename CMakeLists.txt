cmake_minimum_required(VERSION 3.14)
project(RayCaster)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

# Enable compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Allow multi-byte character set compatibility if on MSVC
if(MSVC)
    add_definitions(-DUNICODE -D_UNICODE)
    add_compile_options("/source-charset:utf-8")
endif()

# Add executable
add_executable(RayCaster src/main.cpp)

# Include your own project headers
target_include_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Platform-specific SFML handling
if(WIN32)
    target_link_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include/SFML/lib)

    target_link_libraries(RayCaster PRIVATE
        $<$<CONFIG:Debug>:sfml-system-d sfml-window-d sfml-graphics-d sfml-audio-d>
        $<$<CONFIG:Release>:sfml-system sfml-window sfml-graphics sfml-audio>
    )

    # Hide console window
    set_target_properties(RayCaster PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
else()
    # Use system SFML on Linux/macOS
    find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics audio)
    target_link_libraries(RayCaster PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
endif()
