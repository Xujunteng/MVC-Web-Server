#pragma once
#include"HttpRequest.h"
#include"ModelAndView.h"
#include"Service.h"
#include"View.h"

class Controller {
public:
	static std::string index(HttpRequest&);
	static std::string characters(HttpRequest&);
	static std::string characterDetail(HttpRequest& req);
};

