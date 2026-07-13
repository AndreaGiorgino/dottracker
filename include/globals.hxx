#pragma once

#include <filesystem>

#define ANSI_BOLD  "\033[1m"
#define ANSI_RESET "\033[0m"

/**
 * @brief Represents the default configuration file path
 */
static const std::filesystem::path defaultConfigFilepath {
    "$HOME/.config/dottracker/files.conf"};
