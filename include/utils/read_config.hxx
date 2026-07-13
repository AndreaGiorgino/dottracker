#pragma once

#include <generator>
#include <string>

auto read_config(std::string_view filepath) -> std::generator<std::string>;
