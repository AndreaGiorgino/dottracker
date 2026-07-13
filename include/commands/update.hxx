#pragma once

#include <string_view>

/**
 * @brief Sync the sourced files into target
 *
 * @param source The configuration file path
 * @param target The target to update, accepted values are:
 *   - "local"
 *   - "archive"
 */
auto update(std::string_view source, std::string_view target) -> int;
