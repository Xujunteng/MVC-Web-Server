#include "Logger.h"
#include <fstream>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace {
    std::ofstream g_log;
    std::mutex g_mutex;
    bool g_initialized = false;

    std::string timestamp() {
        auto now = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
    #ifdef _WIN32
        localtime_s(&tm, &tt);
    #else
        tm = *std::localtime(&tt);
    #endif
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    void write_line(const char* level, const std::string& msg) {
        std::lock_guard<std::mutex> lock(g_mutex);
        std::string line = "[" + timestamp() + "] " + level + " " + msg + "\n";
        if (g_initialized && g_log.is_open()) {
            g_log.write(line.c_str(), static_cast<std::streamsize>(line.size()));
            g_log.flush();
        }
       
        std::cout << line;
    }
}

void Logger::init(const std::string& filePath) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (g_initialized) return;
    std::filesystem::path p(filePath);
    std::error_code ec;
    std::filesystem::create_directories(p.parent_path(), ec);
    g_log.open(filePath, std::ios::out | std::ios::app | std::ios::binary);
    g_initialized = g_log.is_open();
}

void Logger::info(const std::string& msg) { write_line("INFO", msg); }
void Logger::error(const std::string& msg) { write_line("ERROR", msg); }
