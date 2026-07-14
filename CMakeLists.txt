cmake_minimum_required(VERSION 3.24)

project(
    dottracker
    VERSION 1.3.0
    LANGUAGES CXX
)

#
# Variables
#

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

#
# Dependencies
#

include(FetchContent)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Options.cmake)

FetchContent_Declare(
    tokenizer
    GIT_REPOSITORY git@github.com:AndreaGiorgino/libtokenizer
    GIT_TAG 1.0.0
)

FetchContent_MakeAvailable(tokenizer)

#
# CMake generated files
#

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/version.hxx.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.hxx
    @ONLY)

#
# Target
#

file(
    GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE -Wall -Wextra -pedantic
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC tokenizer
)
