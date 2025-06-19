cmake_minimum_required(VERSION 3.14)
project(RayCaster)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

# Allow multi-byte character set compatibility if on MSVC
if(MSVC)
    add_definitions(-DUNICODE -D_UNICODE)
    add_compile_options("/source-charset:utf-8")
endif()

# Add source file
add_executable(RayCaster src/main.cpp)

# Include directory
target_include_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link SFML libraries
set(SFML_STATIC_LIBRARIES FALSE) # Change to TRUE if you're using static linking
target_link_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include/SFML/lib)

# Link debug/release SFML libs conditionally
target_link_libraries(RayCaster PRIVATE
    $<$<CONFIG:Debug>:sfml-system-d sfml-window-d sfml-graphics-d sfml-audio-d>
    $<$<CONFIG:Release>:sfml-system sfml-window sfml-graphics sfml-audio>
)

target_link_libraries(RayCaster PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

# Optional: Platform-specific tweaks
if(WIN32)
    # Workaround for WinMain signature
    set_target_properties(RayCaster PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
