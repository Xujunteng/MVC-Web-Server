#pragma once
#include"HttpRequest.h"
#include<string>

class HttpRequestParser {
public:
	static void parse(const std::string& rawRequest, HttpRequest& req);

private:
	static std::string urlDecode(const std::string& text);
};
