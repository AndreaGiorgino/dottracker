#include <format>
#include <functional>

#include "filehash.hxx"

auto filehash(std::string_view filepath) noexcept -> std::string {
    return std::format("{:0>20}", std::hash<std::string_view> {}(filepath));
}
