#pragma once
#include <string>

struct enviroment final {
    std::string program {};
    std::string command {};
    std::string target  {};
    std::string sourcePath {};
    bool colorized { true };
};
