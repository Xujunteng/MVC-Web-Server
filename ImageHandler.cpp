// 图片处理器实现
#include "ImageHandler.h"
#include "Logger.h"
#include <fstream>
#include <filesystem>

// 获取图片的Content-Type（目前统一返回image/jpeg）
std::string ImageHandler::getContentType(const std::string&) {
    return "image/jpeg";
}

// 从文件系统加载图片数据到内存
bool ImageHandler::loadImage(
		const std::string& filePath, std::vector<char>& imageData, 
		std::string& contentType) {
    // 创建支持UTF-8路径的文件路径对象
    std::filesystem::path p = std::filesystem::u8path(filePath);

    // 以二进制模式打开文件
    std::ifstream file(p, std::ios::binary);
    if (file.is_open()) {
        // 使用迭代器一次性读取全部文件内容
        imageData.assign(
			(std::istreambuf_iterator<char>(file)), 
			std::istreambuf_iterator<char>());
        // 关闭文件
        file.close();
        // 获取并设置Content-Type
        contentType = getContentType(filePath);
        // 加载成功
        return true;
    }
    // 文件打开失败
    return false;
}

// 处理图片请求，加载图片并通过socket发送
void ImageHandler::handleImageRequest(SOCKET clientSocket, HttpRequest& request) {
    // 创建图片数据缓冲区
    std::vector<char> imageData;
    // 存储Content-Type
    std::string contentType;
    // 去掉开头的斜杠，构建文件路径
    std::string filePath = request.path.substr(1);
    
    // 尝试加载图片文件
    if (loadImage(filePath, imageData, contentType)) {
        // 构建HTTP 200响应头
        std::string header = "HTTP/1.1 200 OK\r\n";
        // 设置内容类型
        header += "Content-Type: " + contentType + "\r\n";
        // 设置内容长度
        header += "Content-Length: " + std::to_string(imageData.size()) 
			+ "\r\n";
        // 设置连接关闭
        header += "Connection: close\r\n";
        // 空行标记头部结束
        header += "\r\n";
        
        // 先发送HTTP响应头
        int bytesSent = send(
			clientSocket, header.c_str(), static_cast<int>(header.size()), 0);
        if (bytesSent == SOCKET_ERROR) {
            Logger::error(u8"Failed to send image header");
        }

        // 再发送图片二进制数据
        bytesSent = send(
			clientSocket, imageData.data(), 
			static_cast<int>(imageData.size()), 0);
        if (bytesSent == SOCKET_ERROR) {
            Logger::error(u8"Failed to send image data");
        }
        // 记录成功发送日志
        Logger::info(u8"Image sent: " + filePath);
    } else {
        // 图片加载失败，构建404响应
        std::string response = "HTTP/1.1 404 NOT FOUND\r\n";
        response += "Content-Type: text/html; charset=utf-8\r\n";
        response += "Content-Length: 23\r\n";
        response += "Connection: close\r\n";
        response += "\r\n";
        response += "<h1>404 NOT FOUND</h1>";
        
        int bytesSent = send(
			clientSocket, response.c_str(), 
			static_cast<int>(response.size()), 0);
        if (bytesSent == SOCKET_ERROR) {
            Logger::error(u8"Failed to send 404 response");
        }
        Logger::error(u8"Image not found: " + filePath);
    }
}
