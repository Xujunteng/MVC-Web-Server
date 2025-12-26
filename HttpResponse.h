#pragma once
#include"HttpServer.h"
#include<string>
#include<vector>
class HttpResponse {
public:
	static std::string response(std::string& html);
	static std::string response(std::string& content, const std::string& contentType);
	static std::string responseBinary(const std::vector<char>& content, const std::string& contentType);
	static std::string response404(const std::string& html);
};