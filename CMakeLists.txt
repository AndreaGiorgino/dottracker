cmake_minimum_required(VERSION 3.11)

project(dottracker
    VERSION 1.2.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

execute_process(
    COMMAND bash -c "echo $HOME"
    OUTPUT_VARIABLE USER_HOME
    OUTPUT_STRIP_TRAILING_WHITESPACE)

if (${USER_HOME} STREQUAL "")
    message(FATAL_ERROR "Cannot get \$HOME enviroment variable")
endif()

set(CONFIG_DIR ${USER_HOME}/.config/dottracker)

message(STATUS "Initializing the configuration directory: [${CONFIG_DIR}]")
file(MAKE_DIRECTORY ${CONFIG_DIR})


message(STATUS "Creating symlink to the configuration file: ")
execute_process(
    COMMAND ln -fs ${CMAKE_CURRENT_SOURCE_DIR}/files.conf ${CONFIG_DIR})

message(STATUS "Creating symlink to the tracked files directory: [${CONFIG_DIR}/files]")
execute_process(
    COMMAND ln -fs ${CMAKE_CURRENT_SOURCE_DIR}/files ${CONFIG_DIR})

# Configure files

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/version.hxx.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.hxx
    @ONLY)

# Target executable

file(GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS src/*.cxx)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_compile_options(${PROJECT_NAME}
    PRIVATE -Wall -Wextra -pedantic)

target_include_directories(${PROJECT_NAME}
    PRIVATE include)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)
