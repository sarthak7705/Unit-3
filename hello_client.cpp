#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main() {
    WSADATA wsa;
    SOCKET sock;
    sockaddr_in serverAddr;

    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

    string msg = "Hello from Client!";
    send(sock, msg.c_str(), msg.size(), 0);

    char buffer[1024];
    int received = recv(sock, buffer, sizeof(buffer), 0);
    buffer[received] = '\0';

    cout << "Server says: " << buffer << endl;

    closesocket(sock);
    WSACleanup();
}