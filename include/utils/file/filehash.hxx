#pragma once

#include <string>

/**
 * @brief Get the hash from the file path
 *
 * @param filepath The file path to generate the hash from
 */
auto filehash(std::string_view filepath) noexcept -> std::string;
