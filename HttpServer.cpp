// HTTP服务器实现，基于Windows Socket API
#include<iostream>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<windows.h>
#include<sstream>
#include"Controller.h"
#include"HttpServer.h"
#include"HttpRequest.h"
#include"HttpRequestParser.h"
#include"Logger.h"
#include"ModelAndView.h"
#include"HttpResponse.h"
#include"View.h"
#include"ImageHandler.h"

// 启动服务器主循环，处理客户端连接和请求
void HttpServer::start(){
	// 设置控制台输出编码为UTF-8，支持中文字符显示
	SetConsoleOutputCP(65001);
	// 设置控制台输入编码为UTF-8
	SetConsoleCP(65001);
	// 初始化日志记录器，将日志写入文件
	Logger::init("output/server.log");
	
	// 初始化Winsock库
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		Logger::error("WSAStartup failed");
		return;
	}
	
	// 创建TCP套接字用于监听客户端连接
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		Logger::error("Socket creation failed");
		WSACleanup();
		return;
	}
	
	// 设置服务器地址结构：IPv4，本机所有网络接口，8080端口
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(8080);
	
	// 将套接字绑定到本地地址和端口
	if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		Logger::error("Bind failed");
		closesocket(serverSocket);
		WSACleanup();
		return;
	}
	
	// 设置套接字监听模式，最多允许SOMAXCONN个待处理连接
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		Logger::error("Listen failed");
		closesocket(serverSocket);
		WSACleanup();
		return;
	}
	Logger::info("Server is listening on port 8080...");
	
	// 主服务器循环：不断接受客户端连接并处理请求
	while (true) {
		// 接受一个客户端连接，创建新的通信套接字
		SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET) {
			// 客户端连接失败，记录错误但继续运行服务器
			Logger::error("Accept failed");
			continue;
		}
		Logger::info("Client connected!");
		
		// 从客户端接收HTTP请求数据
		char buffer[4096] = { 0 };
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
		
		// 检查接收结果：如果失败，关闭套接字继续处理下一个连接
		if (bytesReceived < 0) {
			Logger::error("recv failed");
			closesocket(clientSocket);
			continue;
		}
		
		// 检查客户端是否主动断开连接
		if (bytesReceived == 0) {
			Logger::info("Client disconnected");
			closesocket(clientSocket);
			continue;
		}
		
		// 添加字符串结束标记
		buffer[bytesReceived] = '\0'; 
		
		// 解析HTTP请求字符串，提取方法、路径、查询参数等信息
		HttpRequest req;
		std::string requestStr(buffer, bytesReceived);
		HttpRequestParser::parse(requestStr, req);

		Logger::info(u8"Request: " + req.method + u8" " + req.path);

		// 判断是否请求图片资源，若是则调用图片处理器专门处理
		if (req.path.find(u8"/images/") == 0 || req.path.find(u8"/img/") == 0) {
			ImageHandler::handleImageRequest(clientSocket, req);
			closesocket(clientSocket);
			continue;
		}

		// 根据请求路径调用相应的路由处理器，获取响应HTML内容
		std::string res;
		std::string html = Router::route(req);
		
		// 判断响应内容类型：CSS文件、404错误页面或普通HTML
		if (req.path.find(".css") != std::string::npos) {
			// 若是CSS文件，设置响应头中的Content-Type为text/css
			res = HttpResponse::response(html, "text/css; charset=utf-8");
		} else if (html.find("<h1>404 NOT FOUND</h1>") != std::string::npos) {
			// 若是404错误，使用对应的错误响应格式
			res = HttpResponse::response404(html);
		} else {
			// 普通HTML页面，使用默认响应格式
			res = HttpResponse::response(html);
		}
		
		// 将HTTP响应数据发送给客户端
		int bytesSent = send(clientSocket, res.c_str(), static_cast<int>(res.size()), 0);
		if (bytesSent == SOCKET_ERROR) {
			Logger::error("send failed");
		}

		// 关闭客户端连接套接字，准备处理下一个连接
		closesocket(clientSocket);
	}
	
}