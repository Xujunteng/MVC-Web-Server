#pragma once
#include"HttpServer.h"
#include<string>
class HttpResponse {
public:
	static std::string response(std::string& html);
};