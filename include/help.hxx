#pragma once

#define ANSI_BOLD  "\033[1m"
#define ANSI_RESET "\033[0m"

static constexpr auto helpMessage {
    ANSI_BOLD
    "NAME                                                                       \n"
    ANSI_RESET
    "    dottracker - dotfiles tracker                                          \n"
    "                                                                           \n"
    ANSI_BOLD
    "SYNOPSIS                                                                   \n"
    ANSI_RESET
    "    dottracker [-v | --version] [-h | --help] <command> [<args>]           \n"
    "                                                                           \n"
    ANSI_BOLD
    "DESCRIPTION                                                                \n"
    ANSI_RESET
    "    dottracker is a tracking program for UNIX dotfiles and configurations. \n"
    "                                                                           \n"
    ANSI_BOLD
    "ENVIROMENT                                                                 \n"
    ANSI_RESET
    "    DOTTRACKER_CONFIG                                                      \n"
    "        Defaults to '$HOME/.config/dottracker/files.conf', represents the  \n"
    "        location of the configuration file.                                \n"
    "                                                                           \n"
    "    DOTTRACKER_ARCHIVE                                                     \n"
    "        Required, represents the location of the archived files.           \n"
    "                                                                           \n"
    ANSI_BOLD
    "OPTIONS                                                                    \n"
    ANSI_RESET
    "    -v, --version                                                          \n"
    "        Prints the program version and exit.                               \n"
    "                                                                           \n"
    "    -h, --help                                                             \n"
    "        Prints the program help message and exit.                          \n"
    "                                                                           \n"
    ANSI_BOLD
    "COMMANDS                                                                   \n"
    ANSI_RESET
    "    diff [<-s | --source> <file_path>]                                     \n"
    "        Print a diff of the tracked files:                                 \n"
    "            - OK: local and archive file are in sync.                      \n"
    "            - A:  local file has been added                                \n"
    "            - M:  local file has been modified                             \n"
    "            - D:  local file has been deleted                              \n"
    "                                                                           \n"
    ANSI_BOLD
    "        Options:                                                           \n"
    ANSI_RESET
    "            -s, --source <file_path>                                       \n"
    "                If specified, use the file provided for the diff,          \n"
    "                otherwise DOTTRACKER_CONFIG is used.                       \n"
    "                                                                           \n"
    "    update <target> [<-s | --source> <file_path>]                          \n"
    "        Update files in target:                                            \n"
    "            - local:   archive files overwrites local files.               \n"
    "            - archive: local files overwrites archive files.               \n"
    "                                                                           \n"
    ANSI_BOLD
    "        Options:                                                           \n"
    ANSI_RESET
    "            -s, --source <file_path>                                       \n"
    "                If specified, use the file provided for the update,        \n"
    "                otherwise DOTTRACKER_CONFIG is used.                       \n"
};
