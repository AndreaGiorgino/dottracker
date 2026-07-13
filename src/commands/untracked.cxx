#include "commands/untracked.hxx"

#include <iostream>
#include <string>
#include <vector>

#include "globals.hxx"
#include "utils/file/filehash.hxx"
#include "utils/read_config.hxx"

namespace fs = std::filesystem;

auto untracked(std::string_view source, bool remove) -> int {
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

    std::vector<std::string> trackedFilespath {};

    for (const auto& filepath : read_config(configFilepath))
        trackedFilespath.push_back(filehash(filepath));

    const auto file_handler {[&](std::string_view hash) -> void {
        if (const auto it {std::find(
                trackedFilespath.begin(), trackedFilespath.end(), hash)};
            it != trackedFilespath.end())
            return;

        std::print(std::cout, ANSI_BOLD "❌ Untracked " ANSI_RESET ": {}", hash);
        if (!remove) {
            std::cout << std::endl;
            return;
        }

        const auto hashFilepath {archivePath + "/" + std::string {hash}};

        try {
            fs::remove(hashFilepath);
            std::println(std::cout, " (deleted)");
        } catch (const std::exception& ex) {
            std::cout << std::endl;
            std::println(std::cerr, "❌ Cannot delete file: {}", hash);
            return;
        }
    }};

    try {
        for (const auto& entry : fs::directory_iterator(archivePath))
            file_handler(entry.path().filename().string());
    } catch (const std::exception& ex) {
        std::cerr << "❌ " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
