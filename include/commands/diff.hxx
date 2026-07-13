#pragma once

#include <filesystem>
#include <string_view>

static const std::filesystem::path defaultConfigFilepath { "$HOME/.config/dottracker/files.conf" };

auto diff(std::string_view source) -> int;
