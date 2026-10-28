#include "io.h"
#include "bst/red_black.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>

// Define the dictionary type for simplicity
using Dictionary = red_black_tree<std::string>;

// Use extern "C" to prevent C++ name mangling, making it easy for Python's ctypes to find these functions.
// Use __declspec(dllexport) for Windows to export these functions from the DLL.
extern "C" {

    /**
     * @brief Creates and initializes the dictionary from a file.
     * 
     * @return A pointer to the created dictionary instance. The caller is responsible for destroying it.
     */
    __declspec(dllexport) Dictionary* create_dictionary() {
        std::cout << "C++: Initializing dictionary..." << std::endl;
        Dictionary* dict = new Dictionary();
        // Note: The path is relative to where the DLL will be run from (the root project folder)
        std::vector<std::pair<std::string, std::string>> df1 = read_txt_double("data/en_cn.txt");
        for(auto const& [english, chinese] : df1){
            dict->tree_insert(english, chinese);
        }
        std::cout << "C++: Dictionary initialized with " << df1.size() << " words." << std::endl;
        return dict;
    }

    /**
     * @brief Destroys the dictionary instance and frees memory.
     * 
     * @param dict_ptr A pointer to the dictionary instance to be destroyed.
     */
    __declspec(dllexport) void destroy_dictionary(Dictionary* dict_ptr) {
        if (dict_ptr) {
            std::cout << "C++: Destroying dictionary." << std::endl;
            delete dict_ptr;
        }
    }

    /**
     * @brief Searches for words with a given prefix.
     * 
     * @param dict_ptr Pointer to the dictionary instance.
     * @param prefix The prefix to search for.
     * @return A dynamically allocated string containing search results.
     *         Format: "word1:meaning1\nword2:meaning2\n...".
     *         The caller MUST free this string using free_string().
     */
    __declspec(dllexport) char* search_word(Dictionary* dict_ptr, const char* prefix) {
        try {
            if (!dict_ptr || !prefix) return nullptr;

            std::string p_str(prefix);
            if (p_str.empty()) return nullptr;

            // 构造上界：简单方法，在末尾追加一个很大的字符
            std::string end_str = p_str;
            end_str += char(127);

            std::vector<node<std::string>*> results = dict_ptr->range_search(p_str, end_str);

            // 过滤结果：只保留以prefix开头的
            std::stringstream ss;
            size_t valid_count = 0;
            for (size_t i = 0; i < results.size(); ++i) {
                node<std::string>* n = results[i];
                if (!n || n == dict_ptr->get_nil()) continue;
                
                // 检查是否以prefix开头
                const std::string& word = n->value;
                if (word.length() >= p_str.length() && 
                    word.substr(0, p_str.length()) == p_str) {
                    if (valid_count > 0) ss << "\n";
                    ss << word << " : ";
                    // 安全访问satellite
                    try {
                        ss << n->satellite;
                    } catch (...) {
                        ss << "(no meaning)";
                    }
                    ++valid_count;
                }
            }

            // 如果没有找到任何结果，返回nullptr
            if (valid_count == 0) {
                return nullptr;
            }

            std::string result = ss.str();
            char* result_str = new char[result.length() + 1];
            strcpy(result_str, result.c_str());
            return result_str;
        } catch (const std::exception& e) {
            std::cerr << "C++ Exception in search_word: " << e.what() << std::endl;
            return nullptr;
        } catch (...) {
            std::cerr << "C++ Unknown exception in search_word" << std::endl;
            return nullptr;
        }
    }

    /**
     * @brief Adds a new word or updates an existing one.
     * 
     * @param dict_ptr Pointer to the dictionary instance.
     * @param word The word to add.
     * @param meaning The meaning of the word.
     * @return int 1 if the word was newly added, 0 if it was updated.
     */
    __declspec(dllexport) int add_word(Dictionary* dict_ptr, const char* word, const char* meaning) {
        if (!dict_ptr || !word || !meaning) return -1;
        
        std::string w(word);
        std::string m(meaning);

        node<std::string>* existing = nullptr;
        try {
            existing = dict_ptr->tree_search(w);
        } catch (...) {
            existing = nullptr;
        }
        
        if (existing && existing != dict_ptr->get_nil()) {
            existing->satellite = m; // Update
            return 0;
        } else {
            dict_ptr->tree_insert(w, m); // Add new
            return 1;
        }
    }

    /**
     * @brief Deletes a word from the dictionary.
     * 
     * @param dict_ptr Pointer to the dictionary instance.
     * @param word The word to delete.
     * @return int 1 if deletion was successful, 0 if the word was not found.
     */
    __declspec(dllexport) int delete_word(Dictionary* dict_ptr, const char* word) {
        if (!dict_ptr || !word) return 0;

        std::string w(word);
        node<std::string>* to_delete = nullptr;
        try {
            to_delete = dict_ptr->tree_search(w);
        } catch (...) {
            to_delete = nullptr;
        }

        if (!to_delete || to_delete == dict_ptr->get_nil()) {
            return 0; // Not found
        } else {
            dict_ptr->tree_delete(to_delete);
            return 1; // Deleted
        }
    }

    /**
     * @brief Frees the memory of a string allocated by C++ functions.
     * 
     * @param str_ptr Pointer to the character array to be freed.
     */
    __declspec(dllexport) void free_string(char* str_ptr) {
        if (str_ptr) {
            delete[] str_ptr;
        }
    }
}
