#pragma once
#include <string>

namespace Logger {
    void init(const std::string& filePath);
    void info(const std::string& msg);
    void error(const std::string& msg);
}
