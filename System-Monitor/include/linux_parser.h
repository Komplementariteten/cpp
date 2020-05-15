#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <iostream>
#include <map>

#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT
#endif

namespace LinuxParser {
// Paths
    const std::string kProcDirectory{"/proc/"};
    const std::string kCmdlineFilename{"/cmdline"};
    const std::string kCpuinfoFilename{"/cpuinfo"};
    const std::string kStatusFilename{"/status"};
    const std::string kStatFilename{"/stat"};
    const std::string kUptimeFilename{"/uptime"};
    const std::string kMeminfoFilename{"/meminfo"};
    const std::string kVersionFilename{"/version"};
    const std::string kOSPath{"/etc/os-release"};
    const std::string kPasswordPath{"/etc/passwd"};
    const std::string kSkipParsing{"SkipParsing"};

    const std::regex kStatusRe{"([[:alpha:]_]{1,}):[[:space:]]{1,}(([[:alnum:]/]{1,})[,[:blank:]-]*)+", std::regex::extended | std::regex::icase};


    class ParseToken {
    private:
        std::string key_;
        std::regex value_re_ = {};
        std::vector<std::string>* values_;
        bool is_valid_ = false;
    public:
        ParseToken(const std::string k, std::regex re);

        ParseToken();

        const std::string Key() const;

        std::vector<std::string> Value();

        bool IsValid() const;

        void ProcessValue(std::string v);
        int Status = 0;
    };

    class ResultCache {
    public:
        ResultCache();
        std::shared_ptr<std::vector<std::string>> Result() const;
        void Update(std::vector<std::string>* result);
        std::chrono::time_point<std::chrono::steady_clock>& LastUpdated();
    private:
        std::shared_ptr<std::vector<std::string>> result_;
        std::chrono::time_point<std::chrono::steady_clock> last_updated_;
    };

    class FileCache {
    public:
        FileCache(const std::string file_path);
        ~FileCache();
        std::string Key() const;
        std::vector<std::string> Value() const;
        bool IsValid() const;
    private:
         void update();
         std::string key_;
         std::vector<std::string>* lines_;
         bool is_valid_;
         void ReadFileAsLines();
    };

    class FileReaderSingleton{
    private:
        bool MatchTokens(std::vector<std::string> text);
        std::map<std::string, std::unique_ptr<LinuxParser::ParseToken>> token_map_;
        std::map<std::string, std::unique_ptr<LinuxParser::FileCache>> file_cache_;

        FileReaderSingleton();
        FileReaderSingleton(FileReaderSingleton const&);
        void operator=(FileReaderSingleton const&);
    public:
        static FileReaderSingleton& GetInstance(){
            static FileReaderSingleton instance;
            return instance;
        }
        std::vector<std::string> Find(const std::string& file, const std::string& token);
    };

// System
    float MemoryUtilization();

    long UpTime();

    std::vector<int> Pids();

    int TotalProcesses();

    int RunningProcesses();

    std::string OperatingSystem();

    std::string Kernel();

// CPU
    enum CPUStates {
        kUser_ = 0,
        kNice_,
        kSystem_,
        kIdle_,
        kIOwait_,
        kIRQ_,
        kSoftIRQ_,
        kSteal_,
        kGuest_,
        kGuestNice_
    };


    std::vector<std::string> CpuUtilization();

    long Jiffies();

    long ActiveJiffies();

    long ActiveJiffies(int pid);

    long IdleJiffies();

// Processes
    std::string Command(int pid);

    std::string Ram(int pid);

    std::string Uid(int pid);

    std::string User(int pid);

    long int UpTime(int pid);

    const std::vector<std::string>& ReadFileAsLines(const std::string file_path);

    bool MatchInLine(const std::vector<std::string>);

};  // namespace LinuxParser

#endif