#pragma once

#include <string_view>

/**
 * @brief Check if the provided files are equals
 *
 * @param filepath1 The first file path
 * @param filepath2 The second file path
 */
auto files_equals(std::string_view filepath1, std::string_view filepath2) -> bool;
