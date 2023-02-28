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
  	user_ = users_.getUser(LinuxParser::Uid(pid_));
  	command_ = LinuxParser::Command(pid_);
  	cpu_util_ = LinuxParser::CpuUtilization(pid_);
    ram_ = LinuxParser::Ram(pid_);
    uptime_ = LinuxParser::UpTime(pid_);                                    
}


// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
	return cpu_util_;
}

// TODO: Return the command that generated this process
string Process::Command() const { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() const { return ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { 
  return user_; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return CpuUtilization() < a.CpuUtilization() ;
}
bool Process::operator>(Process const& a) const {
  return CpuUtilization() > a.CpuUtilization() ;
  //return !(*this < a) ;
}