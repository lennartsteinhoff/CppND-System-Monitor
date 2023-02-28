#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "users.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid() const;                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command() const;                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram() const;                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  bool operator>(Process const& a) const;

  // TODO: Declare any necessary private members
 private:
    int pid_;
  	std::string user_;
  	std::string command_;
  	float cpu_util_;
    string ram_;
  	long int uptime_;
  	Users users_;
};

#endif