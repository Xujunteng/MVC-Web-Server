#include "Router.h"
#include "Controller.h"


void Router::addRoute(const std::string& path, Handler handler) {
	routes[path] = handler;
}

std::string Router::route(HttpRequest& req) {
	if (req.path == "/"||req.path=="/index") {
		return Controller::index(req);
	}
	else if (req.path == "/View/characters") {
		return Controller::characters(req);
	}
	else if (req.path == "/character") {
		return Controller::characterDetail(req);
	}
	else if (req.path == "/favicon.ico") {
		return "";
	}
	return "<h1>404 NOT FOUND<h1>";
}

