#include <filesystem>
#include <iostream>
#include <print>

#include "commands/diff.hxx"
#include "commands/untracked.hxx"
#include "commands/update.hxx"
#include "utils/help.hxx"
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

/**
 * @brief Check if the program enviroment variables are set
 */
auto check_enviroment(void) noexcept -> void {
    if (!getenv("DOTTRACKER_CONFIG"))
        std::println(std::clog,
            "⚠️ Missing enviroment variable \"DOTTRACKER_CONFIG\", "
            "defaulting to {:?}.",
            defaultConfigFilepath.string());

    if (!getenv("DOTTRACKER_ARCHIVE"))
        std::println(std::clog,
            "⚠️ Missing required enviroment variable \"DOTTRACKER_ARCHIVE\", "
            "some commands may not be available.");
}

auto main(int argc, char** argv) -> int {
    /**
     * @brief Get the argument at the given index, returns an empty string
     * if out of bounds
     *
     * @param index The argument index
     */
    const auto get_arg {[&](int index) -> std::string {
        if (index < 0 || index >= argc)
            return {};
        else
            return {*(argv + index)};
    }};

    const auto command {get_arg(1)};
    if (command.empty() || command == "-h" || command == "--help") {
        // print the help message and exit
        print_help();
        return 0;
    } else if (command == "-v" || command == "--version") {
        // print the version and exit
        print_version();
        return 0;
    }

    if (command == "diff") {
        check_enviroment();

        std::string source {};

        for (int i {2}; i < argc; i++) {
            const auto arg {get_arg(i)};

            if (arg.empty())
                continue;
            else if (arg == "-s" || arg == "--source") {
                if (!source.empty()) {
                    std::println(
                        std::cerr, "❌ Source is already set to {:?}.", source);
                    return 1;
                } else
                    source = get_arg(++i);
            } else {
                std::println(std::cerr,
                    "❌ Unknow option {:?} for command {:?}.", arg, command);
                print_help();
                return 1;
            }
        }

        if (const auto ret {diff(source)}; ret != 0) return ret;
    } else if (command == "update") {
        check_enviroment();

        std::string target {};
        std::string source {};

        for (int i {2}; i < argc; i++) {
            const auto arg {get_arg(i)};

            if (arg.empty())
                continue;
            else if (arg == "-s" || arg == "--source") {
                if (!source.empty()) {
                    std::println(
                        std::cerr, "❌ Source is already set to {:?}.", source);
                    return 1;
                } else
                    source = get_arg(++i);
            } else if (*arg.begin() == '-') {
                std::println(std::cerr,
                    "❌ Unknow option {:?} for command {:?}.", arg, command);
                print_help();
                return 1;
            } else {
                if (!target.empty()) {
                    std::println(
                        std::cerr, "❌ Target is already set to {:?}.", target);
                } else
                    target = arg;
            }
        }

        if (const auto ret {update(source, target)}; ret != 0) return ret;
    } else if (command == "untracked") {
        check_enviroment();

        std::string source {};
        bool remove {false};

        for (int i {2}; i < argc; i++) {
            const auto arg {get_arg(i)};

            if (arg.empty())
                continue;
            else if (arg == "-s" || arg == "--source") {
                if (!source.empty()) {
                    std::println(
                        std::cerr, "❌ Source is already set to {:?}.", source);
                    return 1;
                } else
                    source = get_arg(++i);
            } else if (arg == "--delete") {
                if (remove) {
                    std::println(std::cerr, "❌ Delete is already set.");
                    return 1;
                } else
                    remove = true;
            } else {
                std::println(std::cerr,
                    "❌ Unknow option {:?} for command {:?}.", arg, command);
                print_help();
                return 1;
            }
        }

        if (const auto ret {untracked(source, remove)}; ret != 0) return ret;
    } else {
        std::println(std::cerr, "❌ Unknown command {:?}.", command);
    }

    return 0;
}
