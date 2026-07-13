#pragma once

#include <string_view>

/**
 * @brief Execute a diff between the sourced files and the archived ones
 *
 * @param source The configuration file path
 */
auto diff(std::string_view source) -> int;
