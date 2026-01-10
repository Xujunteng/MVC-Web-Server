// 路由器实现，负责URL路由和静态资源处理
#include "Router.h"
#include "Controller.h"
#include <fstream>
#include <sstream>

// 全局路由表，存储所有URL到处理函数的映射
std::map<std::string, Router::Handler> Router::routes{};
// 初始化标志，确保routes只初始化一次
bool Router::initialized = false;

// 添加一个路由到路由表
void Router::addRoute(const std::string& path, Handler handler) {
	// 将路径映射到对应的处理函数
	routes[path] = handler;
}

// 初始化所有路由映射
void Router::ensureInit() {
	// 如果已经初始化过，直接返回
	if (initialized) return;
	// 添加根路径路由
	addRoute("/", Controller::index);
	// 添加/index路径路由，同样指向首页
	addRoute("/index", Controller::index);
	// 添加角色列表页面路由
	addRoute("/characters", Controller::characters);
	// 添加单个角色详情页面路由
	addRoute("/character", Controller::characterDetail);
	// 标记已初始化
	initialized = true;
}

// 根据请求路径分发到相应的处理函数或静态资源
std::string Router::route(HttpRequest& req) {
	// 确保路由表已初始化
	ensureInit();

	// 空路径视为无效请求
	if (req.path.empty()) {
		return "<h1>404 NOT FOUND</h1>";
	}

	// 忽略浏览器自动请求的favicon
	if (req.path == "/favicon.ico") {
		return "";
	}

	// 处理CSS静态文件请求
	if (req.path.find("/View/css/") == 0) {
		// 去掉开头的斜杠构建文件路径
		std::string filePath = req.path.substr(1);
		// 尝试打开CSS文件
		std::ifstream file(filePath);
		if (file.is_open()) {
			// 文件存在，读取全部内容
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}
		// CSS文件不存在，返回注释形式的错误
		return "/* CSS file not found */";
	}

	// 在路由表中查找匹配的路径
	auto it = routes.find(req.path);
	if (it != routes.end()) {
		// 找到匹配路由，调用对应的处理函数
		return it->second(req);
	}

	// 未找到匹配路由，返回404
	return "<h1>404 NOT FOUND</h1>";
}

