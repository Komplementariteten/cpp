#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <linux_parser.h>
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  Process(int pid);
  void UpdateProcess();
  // TODO: Declare any necessary private members
 private:
    int pid_;
    std::string command_;
    float cpuutilization_;
    long int uptime_;
    std::string uid_;
    std::string ram_;
    std::chrono::time_point<std::chrono::steady_clock> last_updated_;
    const std::chrono::microseconds update_interval_ = std::chrono::microseconds(400);
};

#endif