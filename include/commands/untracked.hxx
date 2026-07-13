#pragma once

#include <string_view>

/**
 * @brief Look for not sourced archived files and optionally remove them
 *
 * @param source The configuration file path
 * @param remove If the files should be removed
 */
auto untracked(std::string_view source, bool remove) -> int;
