#include <iostream>
#include <thread>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

const int PORT = 8080;
const int MAX_BUFFER = 1024;

#include "HTTPMessage.h"
#include "HTTPParser.h"

void handleClient(SOCKET clientSock, sockaddr_in clientAddr) {
    char buf[MAX_BUFFER];
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
    int clientPort = ntohs(clientAddr.sin_port);

    std::cout << "New connection from " << clientIP << ":" << clientPort << std::endl;

    // Handle client messages
    while (true) {
        memset(buf, 0, MAX_BUFFER);
        int bytesRead = recv(clientSock, buf, MAX_BUFFER - 1, 0);

        if (bytesRead <= 0) {
            std::cout << "Client " << clientIP << ":" << clientPort << " disconnected" << std::endl;
            break;
        }

        try
        {

            HTTPMessage message = HTTPParser::parse(std::string(buf));
            std::cout << message.to_string() << std::endl;
        }
        catch (const HTTPException& e)
        {
            std::cout << "Error in parsing message: " << e.what() << std::endl;
        }


        // Echo back to client
        std::string response = "Echo: " + std::string(buf);
        send(clientSock, response.c_str(), (int)response.length(), 0);
    }

    closesocket(clientSock);
}

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSock == INVALID_SOCKET) {
        std::cerr << "Failed to create socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Allow socket reuse
    char opt = 1;
    setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }

    if (listen(serverSock, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSock);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    std::vector<std::thread> threads;

    while (true) {
        sockaddr_in clientAddr;
        int clientLen = sizeof(clientAddr);

        SOCKET clientSock = accept(serverSock, (sockaddr*)&clientAddr, &clientLen);
        if (clientSock == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        // Create new thread for each client
        threads.emplace_back(handleClient, clientSock, clientAddr);
        threads.back().detach(); // Detach so thread runs independently
    }

    closesocket(serverSock);
    WSACleanup();
    return 0;
}