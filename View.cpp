#include"View.h"
#include<fstream>
#include<sstream>
#include<filesystem>
#include<windows.h>

std::string readFile(const std::string& path) {
	std::ifstream infile(path);
	if (!infile) return u8"<h1>模板文件未找到: " + path + "</h1>";
	std::stringstream ss;
	ss << infile.rdbuf();
	return ss.str();
}

std::string View::renderFromView(ModelAndView& mv) {
	std::string html = readFile( "View/"+mv.viewName);
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
