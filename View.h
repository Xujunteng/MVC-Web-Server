#pragma once
#include"ModelAndView.h"
#include<string>

class View {
public:
	static std::string renderFromView(ModelAndView& mv);
	static std::string readFile(const std::string& path);
};