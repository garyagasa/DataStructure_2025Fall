#include <iostream>
#include <string>
#include <vector>
#include "calculator.h"

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

extern "C" {
    // Export Function
    DLL_EXPORT int calculate_expression(const char* expression_c_str) {
        if (!expression_c_str) {
            return 0; // NULL Pointer
        }

        try {
            std::string expression = expression_c_str;
            if (expression.empty()) return 0;
            
            // Catch Possible Errors
            std::cout << "Expression: " << expression << std::endl;
            int result = cal(expression);
            std::cout << "Result: " << result << std::endl;
            return result;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return -99999999; // return error code
        } catch (...) {
            std::cerr << "Unkown Error" << std::endl;
            return -99999999; // retrurn error code
        }
    }
}