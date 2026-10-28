#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

vector<pair<string, string>> read_txt_double(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw invalid_argument("Cannot open the file");
    }

    vector<pair<string, string>> ret;
    std::string line;

    while (std::getline(file, line)) {      //read row by row
        stringstream ss(line);
        string english, chinese;
        if(getline(ss, english,' ') && getline(ss, chinese))
            ret.emplace_back(english, chinese);
        else{
            throw runtime_error("invalid line format");
        }
    }

    file.close();
    return ret;
}

vector<string> read_txt_single(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw invalid_argument("Cannot open the file");
    }

    vector<string> ret;
    std::string line;

    while (std::getline(file, line)) {      //read row by row
        stringstream ss(line);
        string english;
        if(getline(ss, english))
            ret.push_back(english);
        else{
            throw runtime_error("invalid line format");
        }
    }

    file.close();
    return ret;
}