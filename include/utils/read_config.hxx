#pragma once

#include <generator>
#include <string>

/**
 * @brief Read the configuration file, expand enviroment variables and return in
 *        a stream the valid lines
 *
 * @param filepath The configuration file to read from
 */
auto read_config(std::string_view filepath) -> std::generator<std::string>;
