// HTTP请求解析器类，解析原始HTTP请求字符串
#pragma once
#include"HttpRequest.h"
#include<string>

class HttpRequestParser {
public:
	// 解析原始HTTP请求字符串为HttpRequest对象
	static void parse(const std::string& rawRequest, HttpRequest& req);

private:
	// URL解码函数，处理%编码和+号
	static std::string urlDecode(const std::string& text);
};
