//
// Created by parallels on 08.05.20.
//

#ifndef MONITOR_MAIN_H
#define MONITOR_MAIN_H

class TestClass {
public:
    TestClass(std::string n) : name_(n) {}
    std::string Name() const {
        return name_;
    }
private:
    std::string name_;
};

#endif //MONITOR_MAIN_H
