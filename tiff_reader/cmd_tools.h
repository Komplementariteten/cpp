//
// Created by me on 11.11.23.
//

#ifndef CMD_TOOLS_H
#define CMD_TOOLS_H
#include <functional>
#include <string>

namespace cmdtools {
    struct Argument {
        std::string name;
        std::string hint;
        char short_name;
        std::function<void(const std::string &)> callbak;
    };
    void parse(int argc, const char* argv[]);

    /**
     * Registes a Callback foir a specific argument, anything starting with h
     * is already taken by help.
     * \brief registers a cli-parameter callback
     * \param argument parameter name
     * \param help_text hint to be shown in help
     * \param func callback function
     * \return true is successful
     */
    bool reg(const char* argument, const char* help_text, std::function<void(const std::string &)> func);

}

#endif //CMD_TOOLS_H
