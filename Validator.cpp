#include <string>
#include <stdexcept>
#include "Validator.h"

bool Validator::isFloat(const std::string &value) {
    try {
        std::stof(value);
        return true;
    }
    catch (const std::invalid_argument &error) {
        return false;
    }
}

bool Validator::isChar(const std::string &value) {
    for (char i : value) {
        if ('0' <= i && i <= '9') {
            return false;
        }

    }
    return true;
}

bool Validator::isInt(const std::string &value) {
    try {
        std::stoi(value);
        return true;
    }
    catch (const std::invalid_argument &error) {
        return false;
    }
}

