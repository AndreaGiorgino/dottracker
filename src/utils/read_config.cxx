#include "utils/read_config.hxx"

#include <format>

#include "libtokenizer/tokenizer.hxx"

using tokenizer = libtokenizer::tokenizer;

auto read_config(std::string_view filepath) -> std::generator<std::string> {
    tokenizer t {filepath};
    tokenizer::token token {};
    std::string buffer {};

    while (!t.eof()) {
        token = t.get();
        buffer.clear();

        if (token.type == tokenizer::token_t::HASH) {
            // skip comment
            while (!t.eof() && t.get().type != tokenizer::token_t::NEWLINE);
            continue;
        } else if (token.type == tokenizer::token_t::NEWLINE)
            // skip empty line
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

                if (name.empty())
                    throw std::runtime_error(
                        "❌ Cannot expand empty enviroment variable.");

                const auto expanded {getenv(name.c_str())};
                if (expanded == NULL)
                    throw std::runtime_error(std::format(
                        "❌ Cannot expand enviroment variable {:?}.", name));

                buffer += expanded;

                if (next.type == tokenizer::token_t::SLASH) {
                    buffer += next.literal;
                    token = t.get();
                } else
                    token = next;
            } else {
                buffer += token.literal;
                tokenizer::token next {};

                while (!t.eof()) {
                    next = t.get();

                    if (next.type == tokenizer::token_t::SLASH
                        || next.type == tokenizer::token_t::NEWLINE)
                        break;

                    buffer += next.literal;
                }

                if (next.type == tokenizer::token_t::SLASH) {
                    buffer += next.literal;
                    token = t.get();
                } else
                    token = next;
            }
        }

        if (!buffer.empty()) co_yield buffer;
    };
}
