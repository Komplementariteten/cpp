//
// Created by me on 11.11.23.
//

#include "cmd_tools.h"

#include <utility>

namespace cmdtools {
    namespace {
        std::vector<Argument> registry;
        bool is_already_taken_in_registry_or_help(const std::string& arg) {
            if(arg.at(0) == 'h') {
                return true;
            }
            if(auto handle = std::ranges::find_if(registry,   [arg](const Argument& a) {
                return a.name == arg;
            }); handle != std::end(registry)) {
                return true;
            }
            return false;
        }
        std::vector<std::string> vectorize(const int argc, const char* argv[]) {
            std::vector<std::string> args;
            for (auto i = 1; i < argc; ++i) {
                const std::string argument(argv[i]);
                args.push_back(argument);
            }
            return args;
        }
        std::string combine_next_args(const std::vector<std::string>::iterator& vector_iterator) {
            std::string join;
            auto current = *vector_iterator;
            for (; current != vector_iterator->end(); ++vector_iterator)
            if(initial.starts_with('-')) {
                return join;
            }
            std::next(vector_iterator);
            return join;
        }
    }


    auto reg(const char* c_arg, const char* help_text, std::function<void(const std::string &)> func) -> bool {
        if(is_already_taken_in_registry_or_help(c_arg)) {
            return false;
        }
        const std::string argument(c_arg);
        registry.push_back(Argument{argument, help_text,argument.at(0), std::move(func) });
        return true;
    }

    void parse(const int argc, const char* argv[]) {
        auto args_vector = vectorize(argc, argv);
        for(auto it = args_vector.begin(); it != args_vector.end(); ++it) {
            auto argument = *it;
            if(auto handle = std::ranges::find_if(registry,   [argument](const Argument& arg) {
                return ("--" + arg.name) == argument || ("-" + arg.short_name) == argument;
            }); handle != std::end(registry)) {
                auto param_args = combine_next_args(it);
                handle->callbak(param_args);
            }
        }
    }

}
