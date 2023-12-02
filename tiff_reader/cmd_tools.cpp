//
// Created by me on 11.11.23.
//

#include "cmd_tools.h"

#include <iostream>
#include <numeric>
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
        std::string get_parameter(const std::string& all_args, const std::string& argument) {
            const auto start = all_args.find(argument) + argument.length() + 1;
            const auto lenght = all_args.find('-', start) - start - 1;
            return all_args.substr(start, lenght);
        }
        void print_help(const std::string& program_name) {
            std::cout << program_name << " <options>" << std::endl;
            std::cout << "Options:" << std::endl;
            for (const auto & [name, hint, short_name, _]: registry) {
                std::cout << "--" << name << " | -" << short_name << "\t\t" << hint << std::endl;
            }
        }
    }

    void clear() {
        registry.clear();
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
        if(argc == 1) {
            print_help(argv[0]);
            return;
        }
        auto args_vector = vectorize(argc, argv);
        auto all_args = std::accumulate(std::next(args_vector.begin()), args_vector.end(), args_vector[0], [](const std::string &a, const std::string &b) {
            return a + " " + b;
        });
        if(all_args.find("-h") != std::string::npos) {
            print_help(argv[0]);
            return;
        }
        for(auto it = args_vector.begin(); it != args_vector.end(); ++it) {
            auto argument = *it;
            if(auto handle = std::ranges::find_if(registry,   [argument](const Argument& arg) {
                return ("--" + arg.name) == argument || ("-" + arg.short_name) == argument;
            }); handle != std::end(registry)) {
                auto param_args = get_parameter(all_args, argument);
                handle->callbak(param_args);
            }
        }
    }

}
