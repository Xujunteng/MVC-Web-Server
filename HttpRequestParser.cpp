#include"HttpRequestParser.h"
#include<sstream>
#include<cctype>

namespace {
	int hexToInt(char c) {
		if (c >= '0' && c <= '9') return c - '0';
		if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
		if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
		return -1;
	}
}

std::string HttpRequestParser::urlDecode(const std::string& text) {
	std::string result;
	result.reserve(text.size());
	for (size_t i = 0; i < text.size(); ++i) {
		if (text[i] == '%' && i + 2 < text.size() && std::isxdigit(static_cast<unsigned char>(text[i + 1])) && std::isxdigit(static_cast<unsigned char>(text[i + 2]))) {
			int hi = hexToInt(text[i + 1]);
			int lo = hexToInt(text[i + 2]);
			if (hi >= 0 && lo >= 0) {
				result.push_back(static_cast<char>((hi << 4) | lo));
				i += 2;
				continue;
			}
		}
		if (text[i] == '+') {
			result.push_back(' ');
			continue;
		}
		result.push_back(text[i]);
	}
	return result;
}

void HttpRequestParser::parse(const std::string& rawRequest, HttpRequest& req) {
	req.method = "";
	req.path = "";
	req.params.clear();

	if (rawRequest.empty()) {
		return;  
	}

	size_t posMethodEnd = rawRequest.find(' ');
	size_t posPathEnd = rawRequest.find(' ', posMethodEnd + 1);
	
	if (posMethodEnd == std::string::npos || posPathEnd == std::string::npos) {
		return; 
	}
	
	req.method = rawRequest.substr(0, posMethodEnd);
	std::string target = rawRequest.substr(posMethodEnd + 1, posPathEnd - posMethodEnd - 1);
	
	if (target.empty()) {
		return; 
	}
	
	size_t qpos = target.find('?');
	if (qpos == std::string::npos) {
		req.path = urlDecode(target);
	} else {
		req.path = urlDecode(target.substr(0, qpos));
		std::string query = target.substr(qpos + 1);
		
		if (!query.empty()) {
			std::stringstream qs(query);
			std::string pair;
			while (std::getline(qs, pair, '&')) {
				if (pair.empty()) continue;
				size_t eq = pair.find('=');
				if (eq == std::string::npos) {
					req.params[urlDecode(pair)] = "";
				} else {
					req.params[urlDecode(pair.substr(0, eq))] = urlDecode(pair.substr(eq + 1));
				}
			}
		}
	}
}
