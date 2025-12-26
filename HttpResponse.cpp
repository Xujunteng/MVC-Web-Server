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

std::string HttpResponse::response(std::string& content, const std::string& contentType) {
		std::string res = "HTTP/1.1 200 OK\r\n";
		res += "Content-Type: " + contentType + "\r\n";
		res += "Content-Length:" + std::to_string(content.size()) + "\r\n";
		res += "Connection:close\r\n";
		res += "\r\n";
		res += content;
		return res;
	}

std::string HttpResponse::responseBinary(const std::vector<char>& content, const std::string& contentType) {
		std::string header = "HTTP/1.1 200 OK\r\n";
		header += "Content-Type: " + contentType + "\r\n";
		header += "Content-Length:" + std::to_string(content.size()) + "\r\n";
		header += "Connection:close\r\n";
		header += "\r\n";
		std::string res = header;
		res.append(content.begin(), content.end());
		return res;
	}

std::string HttpResponse::response404(const std::string& html) {
		std::string res = "HTTP/1.1 404 NOT FOUND\r\n";
		res += "Content-Type: text/html; charset=utf-8\r\n";
		res += "Content-Length:" + std::to_string(html.size()) + "\r\n";
		res += "Connection:close\r\n";
		res += "\r\n";
		res += html;
		return res;
	}