#include "commands/diff.hxx"

#include <iostream>

#include "globals.hxx"
#include "utils/file/files_equals.hxx"
#include "utils/file/filehash.hxx"
#include "utils/read_config.hxx"

namespace fs = std::filesystem;

auto diff(std::string_view source) -> int {
    std::string archivePath {};
    { // archive folder initialisation
        const auto buffer {getenv("DOTTRACKER_ARCHIVE")};
        if (!buffer) {
            std::println(std::cerr,
                "❌ Missing required enviroment variable "
                "\"DOTTRACKER_ARCHIVE\".");
            return 1;
        }

        archivePath = buffer;
        if (!fs::exists(archivePath)) {
            std::println(
                std::cerr, "❌ Archive folder not found: {:?}", archivePath);
            return 1;
        } else if (!fs::is_directory(archivePath)) {
            std::println(
                std::cerr, "❌ Archive is not a folder: {:?}", archivePath);
            return 1;
        }
    }

    std::string configFilepath {source};
    { // config file initialisation
        if (source.empty()) {
            // fallback to default config filepath
            const auto buffer {getenv("DOTTRACKER_CONFIG")};
            configFilepath = {buffer ? buffer : defaultConfigFilepath};
        }

        if (!fs::exists(configFilepath)) {
            std::println(std::cerr,
                "❌ Source configuration file not found: {:?}", configFilepath);
            return 1;
        } else if (!fs::is_regular_file(configFilepath)) {
            std::println(
                std::cerr, "❌ Source is not a file: {:?}", configFilepath);
            return 1;
        }
    }

    const auto file_handler {[&](std::string_view filepath) -> void {
        const auto filename {fs::path {filepath}.filename().string()};
        const auto hash {filehash(filepath)};
        const auto hashFilepath {archivePath + "/" + hash};

        const auto filenameReport {
            std::format("{:20} (hash: {})", filename, hash)};

        if (!fs::exists(filepath))
            std::println(std::cout, ANSI_BOLD "❌ Deleted" ANSI_RESET " -> {}",
                filename);
        else if (!fs::is_regular_file(filepath)) {
            std::println(std::cerr, "❌ Not a file: {:?}", filepath);
            return;
        } else if (!fs::exists(hashFilepath))
            std::println(std::cout, ANSI_BOLD "➕ Added  " ANSI_RESET " -> {}",
                filenameReport);
        else if (files_equals(filepath, hashFilepath))
            std::println(std::cout, ANSI_BOLD "✅ Synced " ANSI_RESET " -> {}",
                filenameReport);
        else
            std::println(std::cout, ANSI_BOLD "🔃 Updated" ANSI_RESET " -> {}",
                filenameReport);
    }};

    try {
        for (const auto& filepath : read_config(configFilepath))
            file_handler(filepath);
    } catch (const std::exception& ex) {
        std::cerr << "❌ " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
