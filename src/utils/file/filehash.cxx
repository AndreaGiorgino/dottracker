#include "utils/file/filehash.hxx"

#include <format>
#include <functional>

auto filehash(std::string_view filepath) noexcept -> std::string {
    return std::format("{:0>20}", std::hash<std::string_view> {}(filepath));
}
