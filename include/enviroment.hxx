#pragma once
#include <filesystem>
#include <string>

struct enviroment final {
    std::filesystem::path program {};
    std::string command {};
    std::string target  {};
    std::filesystem::path sourcePath {};
    bool colorized { true };
};
