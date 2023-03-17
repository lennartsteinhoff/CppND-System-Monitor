#include "format.h"

#include <string>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  string ss, mm, hh, dd;
  ss = std::to_string(seconds % 60);
  ss.insert(0, 2 - ss.length(), '0');
  mm = std::to_string((seconds / 60) % 60);
  mm.insert(0, 2 - mm.length(), '0');
  hh = std::to_string((seconds / (60 * 60)) % 24);
  hh.insert(0, 2 - hh.length(), '0');
  dd = std::to_string((seconds / (60 * 60 * 24)));
//  dd.insert(0, 2 - dd.length(), '0');
  return string(dd + ":" + hh + ":" + mm + ":" + ss);
}