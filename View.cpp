#include"View.h"
#include<fstream>
#include<sstream>
#include<filesystem>

std::string View::readFile(const std::string& path) {
	std::ifstream infile(path);
	if (!infile.is_open()) {
		return u8"<h1>模板文件未找到: " + path + "</h1>";
	}
	std::stringstream ss;
	if (!(ss << infile.rdbuf())) {
		return u8"<h1>读取文件失败: " + path + "</h1>";
	}
	return ss.str();
}

std::string View::renderFromView(ModelAndView& mv) {
	if (mv.viewName.empty()) {
		return u8"<h1>模板名称为空</h1>";
	}
	std::string html = readFile("View/" + mv.viewName);
	// 检查是否读取失败（包含错误信息）
	if (html.find("<h1>") == 0) {
		return html;
	}
	
	for (auto& pair : mv.data) {
		std::string key = "{{" + pair.first + "}}";
		size_t pos = 0;
		while ((pos = html.find(key, pos)) != std::string::npos) {
			html.replace(pos, key.length(), pair.second);
			pos += pair.second.length();
		}
	}
	return html;
}
