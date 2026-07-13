#pragma once

#include <filesystem>

#define ANSI_BOLD  "\033[1m"
#define ANSI_RESET "\033[0m"

static const std::filesystem::path defaultConfigFilepath {
    "$HOME/.config/dottracker/files.conf"};
