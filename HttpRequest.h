#pragma once
#include<string>
#include<map>

struct HttpRequest {
	std::string method;
	std::string path;
	std::map<std::string, std::string>params;
};