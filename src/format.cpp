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
  mm = std::to_string((seconds / 60) % 60);
  hh = std::to_string((seconds / (60 * 60)) % 24);
  dd = std::to_string((seconds / (60 * 60 * 24)));
  return string(dd + ":" + hh + ":" + mm + ":" + ss);
}