cmake_minimum_required(VERSION 2.6)

# ============================================================================= #
# Subprojects
# ============================================================================= #




# ============================================================================= #
# Project Properties
# ============================================================================= #
project(OpenGE)
set(PROJECT_NAME "OpenGE")
set(VERSION_NUMBER "0.0001a")

# Output directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# GLOB Don't follow symlink
cmake_policy(SET CMP0009 NEW)

# ============================================================================= #
# Source Files
# ============================================================================= #
file(GLOB_RECURSE ENGINE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/Engine/Core/*.cpp")
file(GLOB_RECURSE GAME_SOURCE_FILES "${CMAKE_SOURCE_DIR}/Game/*.cpp")

# ============================================================================= #
# Include directories
# ============================================================================= #
set(INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}")

# ============================================================================= #
# Libraries
# ============================================================================= #

# OpenGL
if(APPLE)
    find_library(OPENGL_LIB OpenGL)
    if(NOT OPENGL_LIB)
        message (FATAL_ERROR "Failed to find OpenGL in your Frameworks directory")
    endif(NOT OPENGL_LIB)
endif(APPLE)

# SDL2
if(APPLE)
    find_library(SDL2_LIB SDL2)
    if(NOT SDL2_LIB)
        message(FATAL_ERROR "Failed to find SDL2 in your Frameworks directory.")
    endif(NOT SDL2_LIB)

    find_library(SDL2_IMAGE_LIB SDL2_image)
    if(NOT SDL2_IMAGE_LIB)
        message(FATAL_ERROR "Failed to find SDL2_image in your Frameworks directory.")
    endif(NOT SDL2_IMAGE_LIB)

    find_library(SDL2_TTF_LIB SDL2_ttf)
    if(NOT SDL2_TTF_LIB)
        message(FATAL_ERROR "Failed to find SDL2_ttf in your Frameworks directory.")
    endif(NOT SDL2_TTF_LIB)
endif(APPLE)

# Boost
set(Boots_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_STATIC_RUNTIME OFF)
set(Boost_DEBUG ON)
find_package(Boost REQUIRED system filesystem python)

# Artemis-Cpp
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Libraries/Artemis-Cpp/include")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Engine/Libraries/Artemis-Cpp")

# json-spirit
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Libraries/json-spirit/include")
set(JSON_SPIRIT_LIBRARY_TYPE STATIC)
set(JSON_SPIRIT_BUILD_DEMOS FALSE)
set(JSON_SPIRIT_BUILD_TESTS FALSE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Engine/Libraries/json-spirit/build")

# ============================================================================= #
# Resources
# ============================================================================= #

# Images
file(GLOB_RECURSE RESOURCE_FILES "${CMAKE_SOURCE_DIR}/Engine/Content/Images/*")
file(GLOB_RECURSE RESOURCE_FILES "${CMAKE_SOURCE_DIR}/Game/Content/Images/*")

# Mac OS X Bundle
if(APPLE)
    set_source_files_properties(
        ${RESOURCE_FILES}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources/Assets/Images")
else(APPLE)
	file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Content" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Engine/Content")
	file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Game/Content" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Game/Content")
endif(APPLE)

# ============================================================================= #
# Executables
# ============================================================================= #
include_directories(${INCLUDE_DIRECTORIES})

if(APPLE)
	set(MACOSX_BUNDLE true)
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME} ${VERSION_NUMBER}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${QUANTUM_VERSION_LONG}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION_NUMBER}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${VERSION_NUMBER}")
    set(MACOSX_BUNDLE_ICON_FILE "${CMAKE_SOURCE_DIR}/Game/Content/Icons/Icon.icns")
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${ENGINE_SOURCE_FILES} ${GAME_SOURCE_FILES} ${RESOURCE_FILES_IMAGES})
else(APPLE)
	add_executable(${PROJECT_NAME} ${ENGINE_SOURCE_FILES} ${GAME_SOURCE_FILES})
endif(APPLE)

target_link_libraries(${PROJECT_NAME}
						${OPENGL_LIB}
						${SDL2_LIB}
						${SDL2_IMAGE_LIB}
						${SDL2_TTF_LIB}
                        ArtemisCpp
                        json_spirit)
