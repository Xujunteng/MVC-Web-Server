#include<iostream>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<windows.h>
#include<sstream>
#include<cctype>
#include"Controller.h"
#include"HttpServer.h"
#include"HttpRequest.h"
#include"Logger.h"
#include"ModelAndView.h"
#include"HttpResponse.h"
#include"View.h"

static int hexVal(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
	if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
	return -1;
}

static std::string urlDecode(const std::string& s) {
	std::string out;
	out.reserve(s.size());
	for (size_t i = 0; i < s.size(); ++i) {
		char c = s[i];
		if (c == '+') {
			out.push_back(' ');
		} else if (c == '%' && i + 2 < s.size()) {
			int hi = hexVal(s[i + 1]);
			int lo = hexVal(s[i + 2]);
			if (hi >= 0 && lo >= 0) {
				char ch = static_cast<char>((hi << 4) | lo);
				out.push_back(ch);
				i += 2;
			} else {
				out.push_back(c);
			}
		} else {
			out.push_back(c);
		}
	}
	return out;
}

void HttpServer::start(){
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	Logger::init("output/server.log");
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		Logger::error("WSAStartup failed");
		return;
	}
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		Logger::error("Socket creation failed");
		WSACleanup();
		return;
	}
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(8080);
	if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		Logger::error("Bind failed");
		closesocket(serverSocket);
		WSACleanup();
		return;
	}
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		Logger::error("Listen failed");
		closesocket(serverSocket);
		WSACleanup();
		return;
	}
	Logger::info("Server is listening on port 8080...");
	while (true) {
		SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET) {
			Logger::error("Accept failed");
			closesocket(serverSocket);
			WSACleanup();
			return;
		}
		Logger::info("Client connected!");
		char buffer[4096] = { 0 };
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
		HttpRequest req;
		std::string requestStr(buffer, bytesReceived);
		Logger::info(std::string("收到请求内容:\n") + requestStr);
		size_t pos1 = requestStr.find(' ');
		size_t pos2 = requestStr.find(' ', pos1 + 1);
		if (pos1 != std::string::npos && pos2 != std::string::npos) {
			req.method = requestStr.substr(0, pos1);
			std::string target = requestStr.substr(pos1 + 1, pos2 - pos1 - 1);
			size_t qpos = target.find('?');
			if (qpos != std::string::npos) {
				req.path = target.substr(0, qpos);
				std::string qs = target.substr(qpos + 1);
				std::stringstream qss(qs);
				std::string pair;
				while (std::getline(qss, pair, '&')) {
					if (pair.empty()) continue;
					size_t eq = pair.find('=');
					if (eq != std::string::npos) {
						std::string key = urlDecode(pair.substr(0, eq));
						std::string val = urlDecode(pair.substr(eq + 1));
						req.params[key] = val;
					} else {
						req.params[urlDecode(pair)] = "";
					}
				}
			} else {
				req.path = target;
			}
			Logger::info(std::string("解析出的 path: ") + req.path);
		} else {
			req.path = "";
		}
		std::string html = Router::route(req);
		std::string res=HttpResponse::response(html);
		send(clientSocket, res.c_str(), static_cast<int>(res.size()), 0);

		closesocket(clientSocket);
	}
	
}