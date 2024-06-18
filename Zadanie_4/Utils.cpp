#include"Utils.h"

std::vector<std::string> splitString(std::string input, char delimiter) {

    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

template <typename T>
std::vector<T> castToType(const std::vector<std::string>& input) {
    std::vector<T> output;
    for (const std::string& i : input) {
        std::istringstream iss(i);
        T value;
        if (iss >> value) {
            output.push_back(value);
        }
    }
    return output;
}

