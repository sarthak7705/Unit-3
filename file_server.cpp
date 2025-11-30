#include <iostream>
#include <fstream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    WSAStartup(MAKEWORD(2,2), &wsa);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 3);

    cout << "Waiting for client...\n";

    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);

    ofstream outFile("received.txt", ios::binary);
    char buffer[1024];
    int bytesRead;

    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        outFile.write(buffer, bytesRead);
    }

    cout << "File received successfully.\n";

    outFile.close();
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}