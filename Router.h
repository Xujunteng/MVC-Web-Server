#pragma once
#include<map>
#include<functional>
#include"HttpRequest.h"
#include"ModelAndView.h"
class Router {
public:
	using Handler = std::function<std::string(HttpRequest&)>;
	void addRoute(const std::string& path, Handler handler);
	static std::string route(HttpRequest& request);
private:
	std::map<std::string, Handler>routes;
};