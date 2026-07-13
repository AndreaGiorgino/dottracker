#pragma once

#include <string_view>

auto filediff(std::string_view filepath1, std::string_view filepath2) -> bool;
