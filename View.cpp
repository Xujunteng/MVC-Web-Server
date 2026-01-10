// 视图渲染实现
#include"View.h"
#include<fstream>
#include<sstream>
#include<filesystem>

// 从磁盘读取视图模板文件
std::string View::readFile(const std::string& path) {
	// 打开模板文件
	std::ifstream infile(path);
	// 检查打开是否成功
	if (!infile.is_open()) {
		return u8"<h1>模板文件未找到: " + path + "</h1>";
	}
	// 使用字符串流缓冲器
	std::stringstream ss;
	// 一次性读取整个文件内容
	if (!(ss << infile.rdbuf())) {
		return u8"<h1>读取文件失败: " + path + "</h1>";
	}
	// 返回整个文件内容
	return ss.str();
}

// 渲染视图模板，替换模板中的占位符
std::string View::renderFromView(ModelAndView& mv) {
	// 验证模板名称非空
	if (mv.viewName.empty()) {
		return u8"<h1>模板名称为空</h1>";
	}
	// 读取模板文件内容
	std::string html = readFile("View/" + mv.viewName);
	// 检查是否读取失败（错误信息以<h1>开头）
	if (html.find("<h1>") == 0) {
		return html;
	}
	
	// 遍历所有数据项进行占位符替换
	for (auto& pair : mv.data) {
		// 构建占位符键（格式：{{key}}）
		std::string key = "{{" + pair.first + "}}";
		size_t pos = 0;
		// 查找并替换所有该占位符
		while ((pos = html.find(key, pos)) != std::string::npos) {
			// 用实际值替换占位符
			html.replace(pos, key.length(), pair.second);
			// 移动位置指针到替换后的内容之后
			pos += pair.second.length();
		}
	}
	// 返回替换后的完整HTML
	return html;
}
