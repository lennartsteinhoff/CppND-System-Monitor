#ifndef HELPER_H
#define HELPER_H

#include "tag_filter.h"
#include "linux_parser.h"

#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;

using namespace LinuxParser;


namespace Helper
{
  vector<string> GetTokenFromFile(string filename, string tag);

  vector<string> Tokenize(string line);

  vector<string> Tokenize(string line, char);

  string GetLine(string, string);
  
  template <typename T>
  T findValueByKey(std::string const &keyFilter, std::string const &filename) {
  	std::string line, key;
  	T value;

  	std::ifstream stream(kProcDirectory + filename);
  	if (stream.is_open()) {
    	while (std::getline(stream, line)) {
      		std::istringstream linestream(line);
      		while (linestream >> key >> value) {
        		if (key == keyFilter) {
          			return value;
        		}	
      		}
    	}
  	}
  	return value;
};

template <typename T>
T getValueOfFile(std::string const &filename) {
  std::string line;
  T value;

  std::ifstream stream(kProcDirectory + filename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  return value;
};



} // namespace Helper

#endif
