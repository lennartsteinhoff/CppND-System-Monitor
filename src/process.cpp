#include "helper.h"
#include "process.h"
#include "linux_parser.h"
#include "users.h"

#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <unistd.h>

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : users_(Users("/etc/passwd"))
{  	
    pid_ = pid; 
}


// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
  std::ifstream file ("/proc/" + std::to_string(pid_) + "/stat");
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

// TODO: Return the command that generated this process
string Process::Command() const { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() const { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { 
  return users_.getUser(LinuxParser::Uid(pid_)); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return CpuUtilization() < a.CpuUtilization() ;
}
bool Process::operator>(Process const& a) const {
  return !(*this < a) ;
}