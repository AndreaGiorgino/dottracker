cmake_minimum_required(VERSION 3.24)

project(
    dottracker
    VERSION 1.3.0
    LANGUAGES CXX
)

#
# Variables
#

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Realease)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

execute_process(
    COMMAND bash -c "echo $HOME"
    OUTPUT_VARIABLE USER_HOME
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (${USER_HOME} STREQUAL "")
    message(FATAL_ERROR "Cannot get \$HOME enviroment variable")
endif()

set(CONFIG_DIR ${USER_HOME}/.config/dottracker)

#
# Dependencies
#

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Options.cmake)

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
    CONFIGURE_DEPENDS src/*.cxx
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
        $<INSTALL_INTERFACE:include>
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PostBuild.cmake)
