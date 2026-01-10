// 图片处理类，处理图片资源的加载和发送
#pragma once
#include <string>
#include <vector>
#include <winsock2.h>
#include "HttpRequest.h"

class ImageHandler {
public:
    // 处理图片请求，加载并发送图片数据
    static void handleImageRequest(
		SOCKET clientSocket, HttpRequest& request);
    // 从文件加载图片数据
    static bool loadImage(
		const std::string& filePath, std::vector<char>& imageData, 
		std::string& contentType);
    // 根据文件扩展名获取Content-Type
    static std::string getContentType(const std::string&);
};
