#include <iostream>
#include <fstream>
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

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Connection failed.\n";
        return 1;
    }

    ifstream inFile("send.txt", ios::binary);
    char buffer[1024];

    while (!inFile.eof()) {
        inFile.read(buffer, sizeof(buffer));
        int bytesRead = inFile.gcount();
        send(sock, buffer, bytesRead, 0);
    }

    cout << "File sent successfully.\n";

    inFile.close();
    closesocket(sock);
    WSACleanup();

    return 0;
}