// HTTP请求解析器实现
#include"HttpRequestParser.h"
#include<sstream>
#include<cctype>

namespace {
	// 将十六进制字符转换为整数
	int hexToInt(char c) {
		if (c >= '0' && c <= '9') return c - '0';
		if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
		if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
		return -1;
	}
}

// URL解码，处理%编码和+号空格
std::string HttpRequestParser::urlDecode(const std::string& text) {
	std::string result;
	result.reserve(text.size());
	for (size_t i = 0; i < text.size(); ++i) {
		if (text[i] == '%' && i + 2 < text.size() && 
			std::isxdigit(static_cast<unsigned char>(text[i + 1])) && 
			std::isxdigit(static_cast<unsigned char>(text[i + 2]))) {
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

// 解析HTTP请求行和查询参数
void HttpRequestParser::parse(const std::string& rawRequest, HttpRequest& req) {
	// 初始化请求对象各字段
	req.method = "";
	req.path = "";
	req.params.clear();

	// 空请求直接返回
	if (rawRequest.empty()) {
		return;  
	}

	// 查找第一个空格（方法结束位置）
	size_t posMethodEnd = rawRequest.find(' ');
	// 查找第二个空格（路径结束位置）
	size_t posPathEnd = rawRequest.find(' ', posMethodEnd + 1);
	
	// 格式不正确，直接返回
	if (posMethodEnd == std::string::npos || posPathEnd == std::string::npos) {
		return; 
	}
	
	// 提取HTTP方法（GET/POST等）
	req.method = rawRequest.substr(0, posMethodEnd);
	// 提取目标URI（路径+查询字符串）
	std::string target = rawRequest.substr(posMethodEnd + 1, posPathEnd - posMethodEnd - 1);
	
	// 目标为空，直接返回
	if (target.empty()) {
		return; 
	}
	
	// 查找问号位置（查询字符串起始）
	size_t qpos = target.find('?');
	if (qpos == std::string::npos) {
		// 没有查询字符串，整个target就是路径
		req.path = urlDecode(target);
	} else {
		// 分离路径和查询字符串
		req.path = urlDecode(target.substr(0, qpos));
		// 提取问号后的查询字符串
		std::string query = target.substr(qpos + 1);
		
		// 解析查询参数
		if (!query.empty()) {
			// 创建字符串流用于分割
			std::stringstream qs(query);
			std::string pair;
			// 按&分割每个参数对
			while (std::getline(qs, pair, '&')) {
				// 跳过空参数
				if (pair.empty()) continue;
				// 查找等号位置
				size_t eq = pair.find('=');
				if (eq == std::string::npos) {
					// 没有等号，键存在但值为空
					req.params[urlDecode(pair)] = "";
				} else {
					// 分割键值对并URL解码后存入映射表
					req.params[urlDecode(pair.substr(0, eq))] = urlDecode(pair.substr(eq + 1));
				}
			}
		}
	}
}
