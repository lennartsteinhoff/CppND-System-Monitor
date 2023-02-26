#include <algorithm>
#include <exception>
#include <fstream>
#include <regex>
#include <string>

#include "tag_filter.h"

using std::string;

TagFilter::TagFilter(const string filename) : filename(filename) {}

string TagFilter::Filter(const string tag) {
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
