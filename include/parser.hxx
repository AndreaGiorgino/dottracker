#pragma once
#include <filesystem>
#include <generator>
#include <string>

class parser final {
    public:
        parser(void) = delete;
        explicit parser(std::filesystem::path filePath);

        parser(const parser&) = delete;
        auto operator =(const parser&) = delete;

        parser(parser&&) = delete;
        auto operator =(parser&&) = delete;

        ~parser(void) noexcept = default;

    public:
        auto lines(void) noexcept -> std::generator<std::string>;

    private:
        std::filesystem::path _filePath {};
};
