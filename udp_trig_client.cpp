#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int main(){
    WSADATA w; SOCKET s; sockaddr_in srv; WSAStartup(MAKEWORD(2,2), &w);
    s = socket(AF_INET, SOCK_DGRAM, 0);
    srv.sin_family=AF_INET; srv.sin_addr.s_addr=inet_addr("127.0.0.1"); srv.sin_port=htons(9090);
    string req;
    cout<<"Enter request (e.g. sin 30): ";
    getline(cin, req);
    sendto(s, req.c_str(), req.size(), 0, (sockaddr*)&srv, sizeof(srv));
    char buf[256]; int r = recvfrom(s, buf, sizeof(buf)-1, 0, NULL, NULL);
    if(r>0){ buf[r]='\0'; cout<<"Result: "<<buf<<"\n"; }
    closesocket(s); WSACleanup(); return 0;
}