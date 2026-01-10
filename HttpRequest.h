// HTTP请求数据结构
#pragma once
#include<string>
#include<map>

// 封装HTTP请求的信息
struct HttpRequest {
	std::string method;
	std::string path;
	std::map<std::string, std::string>params;
};