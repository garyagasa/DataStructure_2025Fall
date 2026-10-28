#include "io.h"
#include "bst/red_black.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <cstring>

// 在包含 windows.h 之前定义 byte,避免与 std::byte 冲突
#define byte win_byte_override
#include <windows.h>
#undef byte

// Define the Dictionary type
using Dictionary = red_black_tree<std::string>;
using namespace std;

extern "C" {
    __declspec(dllexport) char* search_word(Dictionary* dict_ptr, const char* prefix) {
        if (!dict_ptr || !prefix) return nullptr;

        std::string p_str(prefix);
        if (p_str.empty()) return nullptr; // 空前缀直接返回空

        // 构造上界:"ab" -> "ac"
        std::string end_str = p_str;
        int i = end_str.size() - 1;
        while (i >= 0) {
            if ((unsigned char)end_str[i] < 0xFF) {
                end_str[i]++;
                end_str.resize(i + 1);
                break;
            }
            --i;
        }
        if (i < 0) end_str += '\0'; // 全部为0xFF时,补一个字符

        std::vector<node<std::string>*> results = dict_ptr->range_search(p_str, end_str);

        std::stringstream ss;
        for (size_t i = 0; i < results.size(); ++i) {
            if (results[i] && results[i] != dict_ptr->get_nil()) {
                ss << results[i]->value << ":" << results[i]->satellite;
                if (i < results.size() - 1) {
                    ss << "\n";
                }
            }
        }

        char* result_str = new char[ss.str().length() + 1];
        strcpy(result_str, ss.str().c_str());
        return result_str;
    }
}

int main(){
    // 设置控制台输入输出为 UTF-8 编码
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    red_black_tree<string> rb1;
    vector<pair<string, string>> df1 = read_txt_double("data/en_cn.txt");
    
    std::cout << "Initializing the dictionary..........." << std::endl;
    for(auto [english, chinese] : df1){
        rb1.tree_insert(english, chinese);
    }
    std::cout << "Initialize the dictionary complete" << std::endl;

    auto query = [&](string str) -> vector<node<string>*>{
        if (str.empty()) {
            return {};
        }
        string end_str = str;
        end_str.back() = end_str.back() + 1;
        return rb1.range_search(str, end_str);
    };

    string command;
    cout << "\nWelcome to the Red-Black Tree Dictionary!" << endl;
    cout << "Available commands:" << endl;
    cout << "  search <word>  - Find words starting with <word>" << endl;
    cout << "  add <word> <meaning> - Add a new word and its meaning" << endl;
    cout << "  delete <word>  - Delete a word" << endl;
    cout << "  exit           - Exit the program" << endl;
    cout << "-------------------------------------------" << endl;

    while (true) {
        cout << "\n> ";
        getline(cin, command);
        
        stringstream ss(command);
        string cmd, word, meaning;
        
        ss >> cmd;

        if (cmd == "search") {
            ss >> word;
            if(word.empty()){
                cout << "Please enter a word to search." << endl;
                continue;
            }
            cout << "Searching for words starting with \"" << word << "\"..." << endl;
            vector<node<string>*> results = query(word);
            if (results.empty()) {
                cout << "No words found." << endl;
            } else {
                for (const auto& n : results) {
                    cout << "  - " << n->value << ": " << n->satellite << endl;
                }
            }
        } else if (cmd == "add") {
            ss >> word;
            // The rest of the stream is the meaning
            getline(ss, meaning);
            // trim leading space
            if (!meaning.empty() && meaning[0] == ' ') {
                meaning = meaning.substr(1);
            }

            if(word.empty() || meaning.empty()){
                cout << "Usage: add <word> <meaning>" << endl;
                continue;
            }

            node<string>* existing = rb1.tree_search(word);
            if (existing != rb1.get_nil()) {
                cout << "Word \"" << word << "\" already exists. Overwriting." << endl;
                existing->satellite = meaning;
            } else {
                rb1.tree_insert(word, meaning);
                cout << "Added: \"" << word << ": " << meaning << "\"" << endl;
            }

        } else if (cmd == "delete") {
            ss >> word;
            if(word.empty()){
                cout << "Please enter a word to delete." << endl;
                continue;
            }
            node<string>* to_delete = rb1.tree_search(word);
            if (to_delete == rb1.get_nil()) {
                cout << "Word \"" << word << "\" not found." << endl;
            } else {
                rb1.tree_delete(to_delete);
                cout << "Deleted \"" << word << "\"." << endl;
            }
        } else if (cmd == "exit") {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Unknown command. Please use 'search', 'add', 'delete', or 'exit'." << endl;
        }
    }
    
}