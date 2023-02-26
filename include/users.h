#ifndef USERS_H
#define USERS_H

#include <map>
#include <string>

using std::string;

class Users
{
    public:
    Users(string filename);
    string getUser(string uid);

    private:
    std::map<string, string> user_data;
};

#endif