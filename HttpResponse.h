// HTTP响应构建类，生成各种类型的HTTP响应
#pragma once
#include"HttpServer.h"
#include<string>
#include<vector>
class HttpResponse {
public:
	// 生成标准HTML响应
	static std::string response(std::string& html);
	// 生成指定Content-Type的响应
	static std::string response(
		std::string& content, const std::string& contentType);
	// 生成二进制内容响应（如图片）
	static std::string responseBinary(
		const std::vector<char>& content, const std::string& contentType);
	// 生成404错误响应
	static std::string response404(const std::string& html);
};