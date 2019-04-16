//
// Created by anson on 4/16/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include "Client/clientserver.hpp"
#include "fs.hpp"

using namespace std;

void
handleError(string msg) { //错误处理函数
    perror(msg.c_str());
    exit(-1);
}

int
main(int argc, char *argv[]) {
    char * buffer = new char[BUFFER_SIZE];
    int clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        handleError("创建socket失败");
    }
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path));

    if (connect(clientSocket, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        handleError("连接服务端失败");
    }

    string command = "";
    for (int i = 1; i < argc; i++) {
        command += string(argv[i]);
        command += " ";
    }
//    cout<< "    "<< command<< endl;

    if (send(clientSocket, command.c_str(), command.size(), 0) == -1) {
        handleError("发送失败");
    }
    int numOfReaded = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (numOfReaded == -1) {
        handleError("对端已经关闭");
    }
    buffer[numOfReaded] = 0;
    cout << buffer << endl;
    delete[] buffer;
}