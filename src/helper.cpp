#include "tag_filter.h"
#include "helper.h"
#include "linux_parser.h"

#include <string>
#include <vector>
#include <sstream>
#include <istream>

using std::string;
using std::vector;

using namespace LinuxParser;


vector<string> Helper::GetTokenFromFile(string filename, string tag) {
    string line = TagFilter(filename).Filter(tag);
    std::stringstream ss(line);
    string token;
    vector<string> tokens_found;
    std::getline(ss, token, ' '); //throw away frist token
    while (std::getline(ss, token, ' ')) {
      if(token != "") {
        tokens_found.push_back(token);
      }
    }
  return tokens_found;
    
}

vector<string> Helper::Tokenize(string line) {
    string token;
    std::stringstream ss(line);
    vector<string> tokens_found;
    while (std::getline(ss, token, ' ')) {
      if(token != "") {
        tokens_found.push_back(token);
      }
    }
    return tokens_found;
}

vector<string> Helper::Tokenize(string line, char seperator) {
    string token;
    std::stringstream ss(line);
    vector<string> tokens_found;
    while (std::getline(ss, token, seperator)) {
      if(token != "") {
        tokens_found.push_back(token);
      }
    }
    return tokens_found;
}

string Helper::GetLine(string filename, string tag) {
  std::ifstream file(filename);
  string line;
  if (file.is_open()) {
    std::getline(file, line);
    while (line.find(tag) == std::string::npos) {
      if (file.eof()) {
        throw std::runtime_error("No Tag: \"" + string(tag) +
                                 "\" found in: " + filename);
      }
      std::getline(file, line);
    }
    return line;

  } else {
    throw std::runtime_error("Cannot open file: " + filename);
  }
}
