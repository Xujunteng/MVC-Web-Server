// 路由器类，管理URL路径到处理函数的映射
#pragma once
#include<map>
#include<functional>
#include"HttpRequest.h"
#include"ModelAndView.h"
class Router {
public:
	// 路由处理函数类型定义
	using Handler = std::function<std::string(HttpRequest&)>;
	// 添加一个路由映射
	static void addRoute(const std::string& path, Handler handler);
	// 根据请求路径路由到对应的处理函数
	static std::string route(HttpRequest& request);
private:
	// 确保路由表已初始化
	static void ensureInit();
	static bool initialized;
	static std::map<std::string, Handler> routes;
};