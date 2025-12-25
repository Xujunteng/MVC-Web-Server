#include "Router.h"
#include "Controller.h"
#include <fstream>
#include <sstream>

std::map<std::string, Router::Handler> Router::routes{};
bool Router::initialized = false;

void Router::addRoute(const std::string& path, Handler handler) {
	routes[path] = handler;
}

void Router::ensureInit() {
	if (initialized) return;
	addRoute("/", Controller::index);
	addRoute("/index", Controller::index);
	addRoute("/characters", Controller::characters);
	addRoute("/character", Controller::characterDetail);
	initialized = true;
}

std::string Router::route(HttpRequest& req) {
	ensureInit();

	if (req.path.empty()) {
		return "<h1>404 NOT FOUND</h1>";
	}

	if (req.path == "/favicon.ico") {
		return "";
	}

	if (req.path.find("/View/css/") == 0) {
		std::string filePath = req.path.substr(1);
		std::ifstream file(filePath);
		if (file.is_open()) {
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}
		return "/* CSS file not found */";
	}

	auto it = routes.find(req.path);
	if (it != routes.end()) {
		return it->second(req);
	}

	return "<h1>404 NOT FOUND</h1>";
}

