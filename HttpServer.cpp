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
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
		if (bytesReceived < 0) {
			Logger::error("recv failed");
			closesocket(clientSocket);
			continue;
		}
		if (bytesReceived == 0) {
			Logger::info("Client disconnected");
			closesocket(clientSocket);
			continue;
		}
		buffer[bytesReceived] = '\0'; 
		
		HttpRequest req;
		std::string requestStr(buffer, bytesReceived);
		HttpRequestParser::parse(requestStr, req);

		Logger::info(u8"Request: " + req.method + u8" " + req.path);

		if (req.path.find(u8"/images/") == 0 || req.path.find(u8"/img/") == 0) {
			ImageHandler::handleImageRequest(clientSocket, req);
			closesocket(clientSocket);
			continue;
		}

		std::string res;
		
		std::string html = Router::route(req);
		
		if (req.path.find(".css") != std::string::npos) {
			res = HttpResponse::response(html, "text/css; charset=utf-8");
		} else {
			res = HttpResponse::response(html);
		}
		
		int bytesSent = send(clientSocket, res.c_str(), static_cast<int>(res.size()), 0);
		if (bytesSent == SOCKET_ERROR) {
			Logger::error("send failed");
		}

		closesocket(clientSocket);
	}
	
}