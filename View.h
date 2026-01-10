// 视图渲染类，负责模板文件的读取和渲染
#pragma once
#include"ModelAndView.h"
#include<string>

class View {
public:
	// 根据ModelAndView对象渲染视图模板
	static std::string renderFromView(ModelAndView& mv);
	// 读取模板文件内容
	static std::string readFile(const std::string& path);
};