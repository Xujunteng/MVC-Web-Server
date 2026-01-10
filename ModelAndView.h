// 模型与视图数据结构
#pragma once
#include<string>
#include<map>
#include<vector>

// 封装视图名称和模板数据
struct ModelAndView {
	std::string viewName;
	std::map<std::string, std::string>data;
};