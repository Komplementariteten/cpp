//
// Created by me on 11.11.23.
//

#include "cmd_tools.h"

namespace cmdtools {
    namespace {
        std::vector<Argument> registry;
    }


    auto reg(const char* c_arg, const std::function<void(const std::string &)>& func) -> void {
        const std::string argument(c_arg);
        registry.push_back(Argument{argument, argument.at(0), func });
    }

    void parse(const int argc, const char* argv[]) {
        for (auto i = 1; i < argc; ++i) {
            const std::string argument(argv[i]);
            if(auto handle = std::ranges::find_if(registry,   [argument](const Argument& arg) {
                return arg.name == argument && arg.short_name == argument.at(0);
            }); handle != std::end(registry)) {
                handle->callbak(argument);
            }
        }
    }

}
