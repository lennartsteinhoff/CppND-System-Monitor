#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

#include "tag_filter.h"
#include "helper.h"
#include "users.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


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
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float Total = Helper::findValueByKey<float>(filterMemTotal, kMeminfoFilename);// "/proc/memInfo"
  float Free = Helper::findValueByKey<float>(filterMemFree, kMeminfoFilename);
  return (Total - Free) / Total;
}


// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string uptime;

  std::ifstream stream{"/proc/uptime"};
  if (stream.is_open()) {
    std::getline(stream, uptime);
  }
  string uptime_sec;
  std::smatch m;
  std::regex_search(uptime, m,
                    std::regex("([0-9]*[.][0-9]*) ([0-9]*[.][0-9]*)"));

  uptime_sec = m[1];

  return std::stoi(uptime_sec);
}



// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line = TagFilter("/proc/stat").Filter(filterCpu);
  std::stringstream ss(line);
  string token;
  vector<string> cpu_util;
  std::getline(ss, token, ' '); //throw away frist token
  while (std::getline(ss, token, ' ')) {
    if(token != "") {
      cpu_util.push_back(token);
    }
  }
  if(cpu_util.size() != 10) {
    throw std::runtime_error("Parsing /proc/stat: cpu went wrong. Expected 10 Elements, Found: " + std::to_string(cpu_util.size()) );
  }
  return cpu_util;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line = TagFilter("/proc/stat").Filter(filterProcesses);
  line = std::regex_replace(line, std::regex(R"([\D])"), "");
  return stoi(line);
}


// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line = TagFilter("/proc/stat").Filter(filterRunningProcesses);
  line = std::regex_replace(line, std::regex(R"([\D])"), "");
  return stoi(line);
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  return string(Helper::getValueOfFile<string>(to_string(pid) + kCmdlineFilename));
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string vm_size = "n/a";
  try
  {
    vm_size = Helper::GetTokenFromFile("/proc/" + std::to_string(pid) + "/status", "VmSize")[0]; 
    for(uint i = 0; i<3; i++) {
      vm_size.pop_back();
    }
  }
  catch(const std::exception& e)
  {
  }

  return vm_size;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string pid_s = std::to_string(pid);
  string filename("/proc/" + pid_s + "/status");

  string line = Helper::GetLine(filename, filterUID);
  auto tokens = Helper::Tokenize(line, '\t');
  return tokens[1]; 
  }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function


// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::ifstream file ("/proc/" + std::to_string(pid) + "/stat");
  string line;
  std::getline(file, line);
  auto tokens = Helper::Tokenize(line);
  long start_time = std::stoi(tokens[21]) / sysconf(_SC_CLK_TCK);
  long uptime_process = LinuxParser::UpTime() - start_time;
  return uptime_process; 
}


float LinuxParser::CpuUtilization(int pid) { 
  std::ifstream file ("/proc/" + std::to_string(pid) + "/stat");
  if (!file) {
    throw std::runtime_error("process not found");
  }
    
  string line;
  std::getline(file, line);
  auto tokens = Helper::Tokenize(line);
  float utime 		= std::stof(tokens[13]);
  float stime 		= std::stof(tokens[14]);
  float cutime 		= std::stof(tokens[15]);
  float cstime 		= std::stof(tokens[16]);
  float start_time  = std::stof(tokens[21]);

  float cpu_time_sec 	= (utime + stime + cutime + cstime) / sysconf(_SC_CLK_TCK);
  float start_time_sec 	= start_time / sysconf(_SC_CLK_TCK);

  return cpu_time_sec / (LinuxParser::UpTime() - start_time_sec);
}