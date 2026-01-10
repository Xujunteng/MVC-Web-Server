// 日志记录器实现，支持文件和控制台日志输出
#include "Logger.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace {
    // 全局日志文件流和初始化标志
    std::ofstream g_log;
    bool g_initialized = false;

    // 生成当前时间戳字符串
    std::string timestamp() {
        // 获取当前系统时间
        auto now = std::chrono::system_clock::now();
        // 转换为time_t类型
        auto tt = std::chrono::system_clock::to_time_t(now);
        // 转换为本地时间结构
        std::tm tm{};
        localtime_s(&tm, &tt);

        // 格式化为字符串
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    // 写入一行日志到文件和控制台
    void write_line(const char* level, const std::string& msg) {
        // 构建完整的日志行
        std::string line = "[" + timestamp() + "] " + level + " " + msg + "\n";
        // 如果日志系统已初始化，写入文件
        if (g_initialized && g_log.is_open()) {
            g_log.write(line.c_str(), static_cast<std::streamsize>(line.size()));
            // 立即刷新到磁盘
            g_log.flush();
        }
       
        // 同时输出到控制台
        std::cout << line;
    }
}

// 初始化日志系统，创建日志目录和文件
void Logger::init(const std::string& filePath) {
    // 构建文件路径对象
    std::filesystem::path p(filePath);
    // 错误码（用于捕获创建目录的错误）
    std::error_code ec;
    // 递归创建父目录
    std::filesystem::create_directories(p.parent_path(), ec);
    // 以追加模式打开日志文件
    g_log.open(filePath, std::ios::out | std::ios::app | std::ios::binary);
    // 设置初始化标志
    g_initialized = g_log.is_open();
}

// 记录INFO级别日志
void Logger::info(const std::string& msg) { write_line("INFO", msg); }
// 记录ERROR级别日志
void Logger::error(const std::string& msg) { write_line("ERROR", msg); }
