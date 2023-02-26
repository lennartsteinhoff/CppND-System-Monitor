#ifndef HELPER_H
#define HELPER_H

#include "tag_filter.h"

#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;


namespace Helper
{
  vector<string> GetTokenFromFile(string filename, string tag);

  vector<string> Tokenize(string line);

  vector<string> Tokenize(string line, char);

  string GetLine(string, string);

} // namespace Helper

#endif
