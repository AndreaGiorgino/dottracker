#
# Enviroment initialization
#

message(STATUS "Initializing the configuration directory: [${CONFIG_DIR}]")
file(MAKE_DIRECTORY ${CONFIG_DIR})

message(STATUS "Creating symlink to the configuration file: ")
execute_process(
    COMMAND ln -fs ${CMAKE_CURRENT_SOURCE_DIR}/files.conf ${CONFIG_DIR}
)

message(STATUS "Creating symlink to the tracked files directory: [${CONFIG_DIR}/files]")
execute_process(
    COMMAND ln -fs ${CMAKE_CURRENT_SOURCE_DIR}/files ${CONFIG_DIR}
)
