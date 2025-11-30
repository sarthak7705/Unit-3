#include <iostream>
#include <winsock2.h>
#include <cmath>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main(){
    WSADATA w; SOCKET s; sockaddr_in srv, cli; int clilen=sizeof(cli);
    WSAStartup(MAKEWORD(2,2), &w);
    s = socket(AF_INET, SOCK_DGRAM, 0);
    srv.sin_family=AF_INET; srv.sin_addr.s_addr=INADDR_ANY; srv.sin_port=htons(9090);
    bind(s,(sockaddr*)&srv,sizeof(srv));
    cout<<"UDP trig server on port 9090\n";
    char buf[256];
    while(true){
        int r = recvfrom(s, buf, sizeof(buf)-1, 0, (sockaddr*)&cli, &clilen);
        if(r<=0) break;
        buf[r]='\0';
        string req(buf);
        // request format: "func value" e.g. "sin 30" (degrees)
        stringstream ss(req); string fn; double val; ss>>fn>>val;
        double rad = val * M_PI / 180.0;
        double ans=0;
        if(fn=="sin") ans = sin(rad);
        else if(fn=="cos") ans = cos(rad);
        else if(fn=="tan") ans = tan(rad);
        else { string err="ERR Unknown"; sendto(s, err.c_str(), err.size(),0,(sockaddr*)&cli,clilen); continue; }
        string out = to_string(ans);
        sendto(s, out.c_str(), out.size(), 0, (sockaddr*)&cli, clilen);
    }
    closesocket(s); WSACleanup(); return 0;
}