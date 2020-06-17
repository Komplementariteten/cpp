#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>
#include <iostream>

#ifdef _LIBCPP_FILESYSTEM

#include <filesystem>

#endif

#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

/*
 * Functions
 */

std::string as_string(std::vector<std::string> v, std::string suffix) {
    std::string result;
    for (auto s: v) {
        result += s + suffix;
    }
    return result;
}

/*
 * Begin Result Cache
 */

LinuxParser::ResultCache::ResultCache() {
    result_ = std::make_shared<std::vector<std::string>>();
}

void LinuxParser::ResultCache::Update(std::vector<std::string> *result) {
    result_->clear();
    for (std::string result_string: *result) {
#ifdef DEBUG_OUTPUT
        std::cout << "Stroing result " << result_string << std::endl;
#endif
        result_->push_back(result_string);
    }
    last_updated_ = std::chrono::steady_clock::now();
}

std::chrono::time_point<std::chrono::steady_clock> & LinuxParser::ResultCache::LastUpdated() {
    return static_cast<std::chrono::time_point<std::chrono::steady_clock> &>(last_updated_);
}

std::shared_ptr<std::vector<std::string>> LinuxParser::ResultCache::Result() const {
    return result_;
}

/*
 * End Result Cache
 */

/*
 * Begin FileCache
 */

LinuxParser::FileCache::FileCache(const std::string file_path)
        : key_(file_path) {
#ifdef DEBUG_OUTPUT
    std::cout << "New Filecache for " << file_path << std::endl;
#endif
    lines_ = new std::vector<std::string>();
    update();
}
LinuxParser::FileCache::~FileCache() {
}

void LinuxParser::FileCache::update() {
    this->ReadFileAsLines();
}

std::string LinuxParser::FileCache::Key() const {
    return key_;
}

std::vector<std::string> LinuxParser::FileCache::Value() const {
    vector<string > v;
    v.reserve(lines_->size());
    std::copy(lines_->begin(), lines_->end(), std::back_inserter(v));
    return v;
}

bool LinuxParser::FileCache::IsValid() const {
    return is_valid_;
}

void LinuxParser::FileCache::ReadFileAsLines() {
    std::string line;
    std::ifstream filestream(key_);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            lines_->push_back(line);
        }
        is_valid_ = true;
    }
}

/*
 * End FileCache
 */

/*
 * Begin FileReaderSingleton
 */

LinuxParser::FileReaderSingleton::FileReaderSingleton() {
    //Uid
    auto uid_token = new ParseToken("Uid", std::regex("([[:digit:]]+)"));
    token_map_.insert({uid_token->Key(), std::make_unique<ParseToken>(*uid_token)});

    //Ram
    auto ram_token = new ParseToken("VmSize", std::regex("([[:digit:]]+) kB"));
    token_map_.insert({ram_token->Key(), std::make_unique<ParseToken>(*ram_token)});

    // Default
    auto default_token = new ParseToken(kSkipParsing, std::regex("(.*)"));
    token_map_.insert({default_token->Key(), std::make_unique<ParseToken>(*default_token)});
}

std::vector<std::string> LinuxParser::FileReaderSingleton::Find(const std::string &file, const std::string &token) {
#ifdef DEBUG_OUTPUT
    std::cout << "Find in " << file << " Token " << token << std::endl;
#endif
    auto fl_cache = file_cache_.find(file);
    if (fl_cache == file_cache_.end()) {
#ifdef DEBUG_OUTPUT
        std::cout << "New File Cache!" << std::endl;
#endif
        auto fl = std::make_unique<FileCache>(file);
        file_cache_.insert({file, std::move(fl)});
    }
    auto text_lines = file_cache_[file]->Value();
    auto valid = file_cache_[file]->IsValid();
    if (!valid) {
        return std::vector<std::string>();
    }
    this->MatchTokens(text_lines);
    if (token_map_[token]->IsValid()) {
#ifdef DEBUG_OUTPUT
        std::cout << "Found valid token " << as_string(token_map_[token]->Value(), "|") << std::endl;
#endif
        auto result = token_map_[token]->Value();
        return result;
    }
    return std::vector<std::string>();
}

bool LinuxParser::FileReaderSingleton::MatchTokens(std::vector<std::string> text) {
#ifdef DEBUG_OUTPUT
    std::cout << as_string(text, "--") << std::endl;
#endif
    std::smatch token_match;
    bool found_something = false;
    auto size = text.size();
    if (size == 0) {
        return found_something;
    }
    for (auto line: text) {
         if (std::regex_match(line, token_match, kStatusRe)) {
            auto key_str = token_match[1].str();
            // In C++20 use contains
            auto search_el = token_map_.find(key_str);
            if (search_el != token_map_.end()) {
                found_something = true;
                for (auto m: token_match) {
#ifdef DEBUG_OUTPUT
                    std::cout << "#match:" << m.str() << std::endl;
#endif
                    search_el->second->ProcessValue(m.str());
                }
            }
        }
    }
    return found_something;
}

/*
 * End FileReaderSingleton
 */

/*
 * Begin ParseToken
 */

LinuxParser::ParseToken::ParseToken(const std::string k, std::regex re) : key_(k), value_re_(re), is_valid_(false) {
    values_ = new std::vector<std::string>();
}

const std::string LinuxParser::ParseToken::Key() const {
    return this->key_;
}

std::vector<std::string> LinuxParser::ParseToken::Value() {
    std::vector<std::string > result;
    result.reserve(values_->size());
    std::copy(values_->begin(), values_->end(), std::back_inserter(result));
    return result;
}

bool LinuxParser::ParseToken::IsValid() const {
    return this->is_valid_;
}

void LinuxParser::ParseToken::ProcessValue(std::string v) {

    values_->clear();

    if (key_ == kSkipParsing) {
        values_->push_back(v);
        return;
    }
    std::smatch str_match;
    this->Status = 1;
    if (std::regex_match(v, str_match, this->value_re_)) {
        auto s = str_match[1].str();
        this->is_valid_ = true;
        this->Status = 2;
        this->values_->push_back(s);
        this->Status = 3;
    }

    std::cout << std::endl;

}
/*
 * End ParseToken
 */


// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
    string line;
    string key;
    string value;
    std::ifstream filestream(kOSPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ' ', '_');
            std::replace(line.begin(), line.end(), '=', ' ');
            std::replace(line.begin(), line.end(), '"', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "PRETTY_NAME") {
                    std::replace(value.begin(), value.end(), '_', ' ');
                    return value;
                }
            }
        }
    }
    return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
    string os, kernel;
    string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> kernel;
    }
    return kernel;
}

#ifdef _LIBCPP_FILESYSTEM

vector<int> LinuxParser::Pids() {
    std::filesystem::path d(kProcDirectory);
    vector<int> pids;
    for (auto &fs : std::filesystem::directory_iterator(d)) {
        auto file_name_string = fs.path().filename().string();
        if (std::all_of(file_name_string.begin(), file_name_string.end(), isdigit)) {
            int pid = stoi(file_name_string);
            pids.push_back(pid);
        }
    }
    return pids;
}

#else
// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}
#endif

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { return 0.0; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { return 0; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

string LinuxParser::Command(int pid) {
    auto command_file = kProcDirectory + std::to_string(pid) + kCmdlineFilename;
    auto search_results = LinuxParser::FileReaderSingleton::GetInstance().Find(command_file, kSkipParsing);
    if (search_results.size() > 0)
        return search_results[0];
    return string();
}

string LinuxParser::Ram(int pid) {
    std::string uid_file = kProcDirectory + std::to_string(pid) + kStatusFilename;
    auto search_results = LinuxParser::FileReaderSingleton::GetInstance().Find(uid_file, "VmSize");
    if (search_results.size() == 0)
        return "0";
    else
        return search_results[0];
}

std::string LinuxParser::Uid(int pid) {
    std::string uid_file = kProcDirectory + std::to_string(pid) + kStatusFilename;
    auto search_results = LinuxParser::FileReaderSingleton::GetInstance().Find(uid_file, "Uid");
    if (search_results.size() == 0)
        return "0";
    else
        return search_results[0];
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
