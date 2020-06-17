#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) :pid_(pid) {
    UpdateProcess();
}

void Process::UpdateProcess() {
    auto now = std::chrono::steady_clock::now();
    if (now > (update_interval_ + last_updated_)) {
        ram_ = LinuxParser::Ram(pid_);
        uid_ = LinuxParser::Uid(pid_);
        command_ = LinuxParser::Command(pid_);
        cpuutilization_ = LinuxParser::ActiveJiffies(pid_);
        uptime_ = LinuxParser::UpTime(pid_);
        std::cout << "Proc V:" << ram_ << "|" << uid_ << "|" << command_ << "|" << cpuutilization_ << "|" <<  std::endl;
    }
}

int Process::Pid() { return pid_; }

float Process::CpuUtilization() { return cpuutilization_; }

string Process::Command() { return command_; }

string Process::Ram() { return ram_; }

string Process::User() { return uid_; }

long int Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }