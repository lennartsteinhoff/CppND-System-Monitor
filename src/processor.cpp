#include "processor.h"
#include "linux_parser.h"

#include <vector>

using std::vector;
using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string> cpu_util = LinuxParser::CpuUtilization();
    int sum = 0;
    int idle = std::stoi(cpu_util[3]);

    for(auto x: cpu_util) {
        sum += std::stoi(x);
    }

    float sumf(sum);
    float idlef(idle);
    return (1 - idlef/sumf); 
 }