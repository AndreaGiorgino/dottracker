#include "utils/file/files_equals.hxx"

#include <filesystem>
#include <format>
#include <fstream>

namespace fs = std::filesystem;

auto files_equals(std::string_view filepath1, std::string_view filepath2) -> bool {
    if (!fs::exists(filepath1))
        throw std::runtime_error(std::format("File not found: {}", filepath1));
    else if (!fs::is_regular_file(filepath1))
        throw std::runtime_error(
            std::format("Not a regular file: {}", filepath1));

    if (!fs::exists(filepath2))
        throw std::runtime_error(std::format("File not found: {}", filepath2));
    else if (!fs::is_regular_file(filepath2))
        throw std::runtime_error(
            std::format("Not a regular file: {}", filepath2));

    std::ifstream file1Ifs {
        filepath1.data(), std::ifstream::binary | std::ifstream::ate};
    std::ifstream file2Ifs {
        filepath2.data(), std::ifstream::binary | std::ifstream::ate};

    if (file1Ifs.tellg() != file2Ifs.tellg())
        // early exit if size mismatch
        return false;

    file1Ifs.seekg(0, std::ifstream::beg);
    file2Ifs.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char> {file1Ifs.rdbuf()},
        std::istreambuf_iterator<char> {},
        std::istreambuf_iterator<char> {file2Ifs.rdbuf()});
}
