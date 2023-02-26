#ifndef TAGFILTER_H
#define TAGFILTER_H

#include <algorithm>
#include <exception>
#include <fstream>
#include <regex>
#include <string>


using std::string;

class TagFilter {
 public:
  TagFilter(const string filename);
  string Filter(const string tag);  // returns line

 private:
  string filename;
};

#endif