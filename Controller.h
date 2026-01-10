// 控制器类，处理HTTP请求并返回页面内容
#pragma once
#include"HttpRequest.h"
#include"ModelAndView.h"
#include"Service.h"
#include"View.h"

class Controller {
public:
	// 处理首页请求
	static std::string index(HttpRequest&);
	// 处理角色列表页面请求，支持筛选功能
	static std::string characters(HttpRequest&);
	// 处理角色详情页面请求
	static std::string characterDetail(HttpRequest& req);
};

