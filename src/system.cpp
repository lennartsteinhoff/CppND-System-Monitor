#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <regex>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

/*You need to complete the mentioned TODOs in order to satisfy the rubric
criteria "The student will be able to extract and display basic data about the
system."

You need to properly format the uptime. Refer to the comments mentioned in
format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    auto process_ids = LinuxParser::Pids();
    processes_ = {};

    for(const int pid : process_ids) {
      
        if(!LinuxParser::Command(pid).empty()) {
            processes_.emplace_back(pid);
        }
    }

  	std::sort(processes_.begin(), processes_.end(), std::greater<Process>());
    //std::sort(processes_.begin(), processes_.end(), [](const Process &a, const Process &b) {return a < b;});
    return processes_; 

}


// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long System::UpTime() { return LinuxParser::UpTime(); }