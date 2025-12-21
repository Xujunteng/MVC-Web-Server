#include"HttpResponse.h"

std::string HttpResponse::response(std::string& html) {
		std::string res = "HTTP/1.1 200 OK\r\n";
		res += "Content-Type: text/html; charset=utf-8\r\n";
		res += "Content-Length:" + std::to_string(html.size()) + "\r\n";
		res += "Connection:close\r\n";
		res += "\r\n";
		res += html;
		return res;
	}