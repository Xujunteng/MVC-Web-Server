// HTTP服务器类，负责监听端口和处理客户端请求
#pragma once
#include"Router.h"

class HttpServer {
public:
	// 启动HTTP服务器，监听8080端口
	void start();
};