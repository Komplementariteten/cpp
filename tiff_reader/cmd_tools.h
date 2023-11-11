//
// Created by me on 11.11.23.
//

#ifndef CMD_TOOLS_H
#define CMD_TOOLS_H
#include <functional>
#include <string>
#include <map>

namespace cmdtools {
    struct Argument {
        std::string name;
        char short_name;
        std::function<void(const std::string &)> callbak;
    };
    void parse(int argc, char* argv[]);
    void reg(const char* argument, std::function<void(const std::string &)> func);

}

#endif //CMD_TOOLS_H
