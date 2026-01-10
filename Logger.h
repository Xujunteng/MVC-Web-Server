// 日志记录器，提供日志记录功能
#pragma once
#include <string>

namespace Logger {
    // 初始化日志系统，指定日志文件路径
    void init(const std::string& filePath);
    // 记录信息级别日志
    void info(const std::string& msg);
    // 记录错误级别日志
    void error(const std::string& msg);
}
