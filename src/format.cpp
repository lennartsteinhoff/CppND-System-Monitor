#include "format.h"

#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

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
   
  std::stringstream sstream{};

  sstream << std::setw(2) << std::setfill('0') << hh     // HH
     << std::setw(1) << ":"                                    // :
     << std::setw(2) << std::setfill('0') << mm    // MM
     << std::setw(1) << ":"                                    // :
     << std::setw(2) << std::setfill('0') << ss ;  // SS
   
  return sstream.str();
} 

/* string Format::ElapsedTime(long s) {
  std::chrono::seconds seconds{s};

  // return std::chrono::format("%T", seconds); // in C++20 :-)

  std::chrono::hours hours =
      std::chrono::duration_cast<std::chrono::hours>(seconds);

  seconds -= std::chrono::duration_cast<std::chrono::seconds>(hours);

  std::chrono::minutes minutes =
      std::chrono::duration_cast<std::chrono::minutes>(seconds);

  seconds -= std::chrono::duration_cast<std::chrono::seconds>(minutes);

  std::stringstream ss{};

  ss << std::setw(2) << std::setfill('0') << hours.count()     // HH
     << std::setw(1) << ":"                                    // :
     << std::setw(2) << std::setfill('0') << minutes.count()   // MM
     << std::setw(1) << ":"                                    // :
     << std::setw(2) << std::setfill('0') << seconds.count();  // SS

  return ss.str();
}
*/