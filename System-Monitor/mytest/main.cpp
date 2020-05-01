//
// Created by parallels on 30.04.20.
//
#include <filesystem>
#include <iostream>

int main() {
  std::cout << "Start?";
  std::filesystem::path p1 = "/proc/";
  auto it = std::filesystem::directory_iterator(p1);
  for (auto& p : it) {
    std::cout << p.path().filename().string() << std::endl;
  }
}