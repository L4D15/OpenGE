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

# Add cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Tools/cmake-modules")

# Set C++11
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

# ============================================================================= #
# Source Files
# ============================================================================= #
file(GLOB_RECURSE ENGINE_CORE_SOURCE_FILES          "${CMAKE_SOURCE_DIR}/Engine/Core/*.*pp")
file(GLOB_RECURSE ENGINE_COMPONENTS_SOURCE_FILES    "${CMAKE_SOURCE_DIR}/Engine/Components/*.*pp")
file(GLOB_RECURSE ENGINE_ASSETS_SOURCE_FILES        "${CMAKE_SOURCE_DIR}/Engine/Assets/*.*pp")
file(GLOB_RECURSE GAME_SOURCE_FILES                 "${CMAKE_SOURCE_DIR}/Game/*.*pp")

# ============================================================================= #
# Include directories
# ============================================================================= #
set(INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}")

# ============================================================================= #
# Libraries
# ============================================================================= #

message("Searching libraries for ${CMAKE_SYSTEM_NAME}")

# OpenGL
if(APPLE)
    find_library(OPENGL_LIB OpenGL)
    if(NOT OPENGL_LIB)
        message (FATAL_ERROR "Failed to find OpenGL in your Frameworks directory")
    endif(NOT OPENGL_LIB)
else()
    find_package(OpenGL REQUIRED)
    if(NOT OPENGL_FOUND)
        message("Failed to load OpenGL")
    endif()
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
else()
    if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        find_library(SDL2_LIB NAMES SDL2 HINTS "/usr/local/lib")
        find_library(SDL2_IMAGE_LIB NAMES SDL2_image HINTS "/usr/local/lib")
        find_library(SDL2_TTF_LIB NAMES SDL2_ttf HINTS "/usr/local/lib")

        if (NOT SDL2_LIB)
            message("-- [!] Failed to load SDL2 library from /usr/local/lib")
        endif()
        if (NOT SDL2_IMAGE_LIB)
            message("-- [!] Failed to load SDL2_image library from /usr/local/lib")
        endif()
        if (NOT SDL2_TTF_LIB)
            message("-- [!] Failed to load SDL2_ttf library from /usr/local/lib")
        endif()
    endif()
endif(APPLE)

# Boost
set(Boots_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_STATIC_RUNTIME OFF)
set(Boost_DEBUG ON)
find_package(Boost REQUIRED system filesystem thread)

# anax
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Libraries/anax/include")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Engine/Libraries/anax")

# json-spirit
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Libraries/json-spirit/include")
set(JSON_SPIRIT_LIBRARY_TYPE STATIC)
set(JSON_SPIRIT_BUILD_DEMOS FALSE)
set(JSON_SPIRIT_BUILD_TESTS FALSE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Engine/Libraries/json-spirit/build")

# lua
find_package(Lua51 REQUIRED)
find_package(Luabind REQUIRED)
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${LUA_INCLUDE_DIRS} ${LUABIND_INCLUDE_DIRS})

# ============================================================================= #
# Resources
# ============================================================================= #

# Images
file(GLOB_RECURSE RESOURCE_SPRITES "${CMAKE_CURRENT_SOURCE_DIR}/Game/Assets/Sprites/*")

# Scripts
file(GLOB_RECURSE RESOURCE_SCRIPTS "${CMAKE_CURRENT_SOURCE_DIR}/Game/Assets/Scripts/*.lua")

# Scenes
file(GLOB_RECURSE RESOURCE_SCENES "${CMAKE_CURRENT_SOURCE_DIR}/Game/Scenes/*.json")

# Mac OS X Bundle
if(APPLE)
    set_source_files_properties(
        ${RESOURCE_SPRITES}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources/Assets/Sprites")
    set_source_files_properties(
        ${RESOURCE_SCRIPTS}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources/Assets/Scripts")
    set_source_files_properties(
        ${RESOURCE_SCENES}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources/Scenes")
else(APPLE)
	file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Game/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Game/Assets")
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
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE    ${ENGINE_CORE_SOURCE_FILES}
                                                    ${ENGINE_COMPONENTS_SOURCE_FILES}
                                                    ${ENGINE_ASSETS_SOURCE_FILES}
                                                    ${GAME_SOURCE_FILES}
                                                    ${RESOURCE_SPRITES}
                                                    ${RESOURCE_SCRIPTS}
                                                    ${RESOURCE_SCENES})
else(APPLE)
	add_executable(${PROJECT_NAME}  ${ENGINE_CORE_SOURCE_FILES}
                                    ${ENGINE_COMPONENTS_SOURCE_FILES}
                                    ${GAME_SOURCE_FILES})
endif(APPLE)

target_link_libraries(  ${PROJECT_NAME}
						${OPENGL_LIB}
                        ${OPENGL_LIBRARIES}
						${SDL2_LIB}
						${SDL2_IMAGE_LIB}
						${SDL2_TTF_LIB}
                        ${Boost_LIBRARIES}
                        anax
                        json_spirit
                        ${LUA_LIBRARIES}
                        ${LUABIND_LIBRARIES})
