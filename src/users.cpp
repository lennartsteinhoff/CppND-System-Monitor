#include "users.h"
#include "helper.h"

#include <string>
#include <map>
#include <fstream>

using std::string;

Users::Users(string filename) {
    std::ifstream file(filename);
    string line;
    while(getline(file, line)) {
        auto tokens = Helper::Tokenize(line, ':');
        user_data.insert({tokens[2], tokens[0]});
    }
}

string Users::getUser(string uid) {
    auto found = user_data.find(uid);
    if(found == user_data.end()) {
        return uid;
    }
    return found->second;
}