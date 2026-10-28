#include <cstdio>
#include <stdexcept>
#include <string>

int string2index(std::string str){
    /**
     *  (A-Z) : (0-25)
     *  (a-z) : (26-51)
     */
    if(str.size() != 1){
        throw std::invalid_argument("only support single letter string");
    }
    int ret = -1;
    char letter = str[0];
    int little_index = letter - 'a'; 
    int big_index = letter - 'A';
    if(little_index >= 0 && little_index < 26){
        ret = little_index + 26;
    }
    else if(big_index >= 0 && big_index < 26){
        ret = big_index;
    }
    else{
        throw std::invalid_argument("only support english letter");
    }
    return ret;
}

std::string index2string(int idx){
    /**
     *  (A-Z) : (0-25)
     *  (a-z) : (26-51)
     */
    std::string ret;
    if(idx >= 0 && idx < 26){
        ret = std::string(1, 'A' + idx);
    }
    else if(idx >= 26 && idx < 52){
        ret = std::string(1, 'a' + idx - 26);
    }
    else{
        throw std::invalid_argument("index out of range in index2string");
    }
    return ret;
}