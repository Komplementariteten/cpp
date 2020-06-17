//
// Created by parallels on 30.04.20.
//
#include <iostream>
#include <map>
#include "main.h"

int main() {
    std::cout << "Start?";
    std::map<int, TestClass&> m_map = {};

    for (int i = 0; i < 100; ++i) {
        auto m = new TestClass(std::to_string(i) + " AB");
        m_map.insert({i, *m});
    }

    auto el_2 = m_map.at(2);
    auto el_80 = m_map.at(80);
    std::cout << "M is " << m_map.size() << " Big & name of second element " << el_2.Name() << " and 80th " << el_80.Name() << std::endl;
}