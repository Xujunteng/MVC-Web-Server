#pragma once
#include <string>
#include <vector>
#include <winsock2.h>
#include "HttpRequest.h"

class ImageHandler {
public:
    static void handleImageRequest(SOCKET clientSocket, HttpRequest& request);
    
    static bool loadImage(const std::string& filePath, std::vector<char>& imageData, std::string& contentType);

    static std::string getContentType(const std::string&);
};
