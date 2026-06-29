#include <iostream>
#include <print>

#include "help.hxx"
#include "version.hxx"

/**
 * @brief Print the program version
 */
auto print_version(void) noexcept -> void {
    std::println("dottracker version {}", PROJECT_VERSION);
}

/**
 * @brief Print the program help
 */
auto print_help(void) noexcept -> void {
    std::println(helpMessage);
}

auto diff(void) -> int {
    // TODO: function "diff" not implemented yet
    std::println(std::cerr, "function \"diff\" not implemented yet");
    return 1;
}
auto update(std::string_view target, std::string_view source = {}) -> int {
    // TODO: function "update" not implemented yet
    std::println(std::clog,
            "Executing command \"update\":\n"
            "    target: {:?}\n"
            "    source: {:?}",
            target, source);

    if (target.empty()) {
        std::println(std::cerr,
                "Missing target to update.");
        return 1;
    } else if (source.empty()) {
        std::println(std::cerr,
                "Missing source for updating.");
        return 1;
    }

    std::println(std::cerr, "function \"update\" not implemented yet");
    return 1;
}

auto main(int argc, char** argv) -> int {
    /**
     * @brief Get the argument at the given index, returns an empty string
     * if out of bounds
     *
     * @param index The argument index
     */
    const auto get_arg {
        [&](int index) -> std::string {
            if (index < 0 || index >= argc)
                return {};
            else return { *(argv + index) };
        }
    };

    const auto command { get_arg(1) };
    if (command.empty()
            || command == "-h"
            || command == "--help") {
        // print the help message and exit
        print_help();
        return 0;
    } else if (command == "-v"
            || command == "--version") {
        // print the version and exit
        print_version();
        return 0;
    } else if (command == "diff") {
        // TODO: handle options
        if (const auto ret { diff() };
                ret != 0)
            return ret;
    } else if (command == "update") {
        std::string target {};
        std::string source {};

        for (int i { 2 }; i < argc; i++) {
            const auto arg { get_arg(i) };
            if (arg.empty())
                continue;
            else if (arg == "-s"
                    || arg == "--source") {
                if (!source.empty()) {
                    std::println(std::cerr,
                            "Source already set to {:?}.",
                            source);
                    return 1;
                } else source = get_arg(++i);
            } else if (*arg.begin() == '-') {
                std::println(std::cerr,
                        "Unknow option {:?} for command {:?}.",
                        arg, command);
                print_help();
                return 1;
            } else {
                if (!target.empty()) {
                    std::println(std::cerr,
                            "Target is already set to {:?}.",
                            target);
                } else target = arg;
            }
        }

        if (const auto ret { update(target, source) };
                ret != 0)
            return ret;
    } else {
        std::println(std::cerr,
                "Unknown command {:?}.",
                command);
    }

    return 0;
}
