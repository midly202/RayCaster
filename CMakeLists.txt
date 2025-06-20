cmake_minimum_required(VERSION 3.14)
project(RayCaster)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

# Enable compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add executable
add_executable(RayCaster src/main.cpp)

# Include your headers
# target_include_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include/SFML)

# Platform-specific logic
if(WIN32)
    target_link_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include/SFML/libWin)

    target_link_libraries(RayCaster PRIVATE
        $<$<CONFIG:Debug>:sfml-system-d sfml-window-d sfml-graphics-d sfml-audio-d>
        $<$<CONFIG:Release>:sfml-system sfml-window sfml-graphics sfml-audio>
    )

    set_target_properties(RayCaster PROPERTIES WIN32_EXECUTABLE TRUE)

else() # Linux

    target_link_directories(RayCaster PRIVATE ${CMAKE_SOURCE_DIR}/include/SFML/libLin)

    # Runtime linker path for .so files
    set_target_properties(RayCaster PROPERTIES
        BUILD_RPATH "${CMAKE_SOURCE_DIR}/include/SFML/libLin"
    )

    # Explicit full paths to .so files
    target_link_libraries(RayCaster PRIVATE
        ${CMAKE_SOURCE_DIR}/include/SFML/libLin/libsfml-graphics.so
        ${CMAKE_SOURCE_DIR}/include/SFML/libLin/libsfml-window.so
        ${CMAKE_SOURCE_DIR}/include/SFML/libLin/libsfml-system.so
        ${CMAKE_SOURCE_DIR}/include/SFML/libLin/libsfml-audio.so
    )

    # Manually add required system dependencies (optional if already installed)
    # find_library(FLAC_LIB NAMES FLAC)
    # find_library(OGG_LIB NAMES ogg)
    # find_library(VORBIS_LIB NAMES vorbis)
    # find_library(OPENAL_LIB NAMES openal)

    # target_link_libraries(RayCaster PRIVATE ${FLAC_LIB} ${OGG_LIB} ${VORBIS_LIB} ${OPENAL_LIB})

endif()