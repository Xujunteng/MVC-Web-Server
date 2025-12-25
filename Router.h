#pragma once
#include<map>
#include<functional>
#include"HttpRequest.h"
#include"ModelAndView.h"
class Router {
public:
	using Handler = std::function<std::string(HttpRequest&)>;
	static void addRoute(const std::string& path, Handler handler);
	static std::string route(HttpRequest& request);
private:
	static void ensureInit();
	static bool initialized;
	static std::map<std::string, Handler> routes;
};