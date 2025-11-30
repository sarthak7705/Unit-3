#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main() {
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientSize = sizeof(clientAddr);

    WSAStartup(MAKEWORD(2,2), &wsa);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 1);

    cout << "Server running on port 8080...\n";

    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

    char buffer[1024];
    int received = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[received] = '\0';

    cout << "Client says: " << buffer << endl;

    string reply = "Hello from Server!";
    send(clientSocket, reply.c_str(), reply.size(), 0);

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}