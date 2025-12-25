#include "ImageHandler.h"
#include "Logger.h"
#include <fstream>
#include <filesystem>

std::string ImageHandler::getContentType(const std::string&) {
    return "image/jpeg";
}

bool ImageHandler::loadImage(const std::string& filePath, std::vector<char>& imageData, std::string& contentType) {
    std::filesystem::path p = std::filesystem::u8path(filePath);

    std::ifstream file(p, std::ios::binary);
    if (file.is_open()) {
        imageData.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        contentType = getContentType(filePath);
        return true;
    }
    return false;
}

void ImageHandler::handleImageRequest(SOCKET clientSocket, HttpRequest& request) {
    std::vector<char> imageData;
    std::string contentType;
    std::string filePath = request.path.substr(1);
    
    if (loadImage(filePath, imageData, contentType)) {
        std::string header = "HTTP/1.1 200 OK\r\n";
        header += "Content-Type: " + contentType + "\r\n";
        header += "Content-Length: " + std::to_string(imageData.size()) + "\r\n";
        header += "Connection: close\r\n";
        header += "\r\n";
        
        int bytesSent = send(clientSocket, header.c_str(), static_cast<int>(header.size()), 0);
        if (bytesSent == SOCKET_ERROR) {
            Logger::error(u8"Failed to send image header");
        }

        bytesSent = send(clientSocket, imageData.data(), static_cast<int>(imageData.size()), 0);
        if (bytesSent == SOCKET_ERROR) {
            Logger::error(u8"Failed to send image data");
        }
        Logger::info(u8"Image sent: " + filePath);
    } else {
        std::string response = "HTTP/1.1 404 NOT FOUND\r\n";
        response += "Content-Type: text/html; charset=utf-8\r\n";
        response += "Content-Length: 23\r\n";
        response += "Connection: close\r\n";
        response += "\r\n";
        response += "<h1>404 NOT FOUND</h1>";
        
        int bytesSent = send(clientSocket, response.c_str(), static_cast<int>(response.size()), 0);
        if (bytesSent == SOCKET_ERROR) {
            Logger::error(u8"Failed to send 404 response");
        }
        Logger::error(u8"Image not found: " + filePath);
    }
}
