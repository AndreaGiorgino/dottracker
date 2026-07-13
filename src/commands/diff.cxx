#include "commands/diff.hxx"

#include <iostream>

#include "libtokenizer/tokenizer.hxx"

using tokenizer = libtokenizer::tokenizer;

auto diff(std::string_view source) -> int {
    std::string archiveFilepath {};
    {
        const auto envArchiveFilepath {getenv("DOTTRACKER_ARCHIVE")};
        if (!envArchiveFilepath) {
            std::println(std::cerr,
                "❌ Missing required enviroment variable "
                "\"DOTTRACKER_ARCHIVE\".");
            return 1;
        }

        archiveFilepath = envArchiveFilepath;
    }

    std::string configFilepath {};
    if (source.empty()) {
        const auto envConfigFilepath {getenv("DOTTRACKER_CONFIG")};
        configFilepath
            = {envConfigFilepath ? envConfigFilepath : defaultConfigFilepath};
    }

    if (!std::filesystem::exists(configFilepath)) {
        std::println(std::cerr, "❌ Source configuration file not found: {:?}",
            configFilepath);
        return 1;
    }

    const auto file_handler {[&](std::string_view filepath) -> bool {
        // TODO: make files diff
        std::println(std::clog, "filepath: {:?}.", filepath);
        return false;
    }};

    try {
        tokenizer t {configFilepath};
        tokenizer::token token {};
        std::string filepath {};

        while (!t.eof()) {
            token = t.get();
            filepath.clear();

            if (token.type == tokenizer::token_t::HASH) {
                // skip comment
                while (!t.eof() && t.get().type != tokenizer::token_t::NEWLINE);
                continue;
            } else if (token.type == tokenizer::token_t::NEWLINE)
                // skip empty lines
                continue;

            while (!t.eof()) {
                if (token.type == tokenizer::token_t::NEWLINE)
                    break;
                else if (token.type == tokenizer::token_t::SYMBOL
                         && token.literal[0] == '$') {
                    // handle env variable
                    tokenizer::token next {};
                    std::string name {};

                    while (!t.eof()) {
                        next = t.get();

                        if (next.type == tokenizer::token_t::SLASH
                            || next.type == tokenizer::token_t::NEWLINE)
                            break;

                        name += next.literal;
                    }

                    if (name.empty()) {
                        std::println(std::cerr,
                            "❌ Cannot expand empty enviroment variable.");
                        return 1;
                    }

                    const auto expanded {getenv(name.c_str())};
                    if (expanded == NULL) {
                        std::println(std::cerr,
                            "❌ Cannot expand enviroment variable {:?}.", name);
                        return 1;
                    }

                    filepath += expanded;

                    if (next.type == tokenizer::token_t::SLASH) {
                        filepath += next.literal;
                        token = t.get();
                    } else
                        token = next;
                } else {
                    filepath += token.literal;
                    tokenizer::token next {};

                    while (!t.eof()) {
                        next = t.get();

                        if (next.type == tokenizer::token_t::SLASH
                            || next.type == tokenizer::token_t::NEWLINE)
                            break;

                        filepath += next.literal;
                    }

                    if (next.type == tokenizer::token_t::SLASH) {
                        filepath += next.literal;
                        token = t.get();
                    } else
                        token = next;
                }
            }

            if (!filepath.empty()) file_handler(filepath);
        };
    } catch (const std::exception& ex) {
        std::cerr << "❌ " << ex.what() << std::endl;
        return 1;
    }

    std::println(std::cerr, "function \"diff\" not implemented yet");
    return 1;
}
