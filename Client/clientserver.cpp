//
// Created by anson on 4/16/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include "clientserver.hpp"
#include "client.h"
#include "../NameNode/namenode.hpp"
#include "../fs.hpp"
#include "iostream"
#include "../logger.hpp"
#include "unistd.h"


using namespace std;

time_t time1;
Client client;

int
main(void) {
    // 添加 socket 监听
    int serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        handleError("创建socket失败");
    }
    bindToAddress(serverSocket);
    if (listen(serverSocket, BACK_LOG) == -1) {//转为被动模式
        handleError("监听失败");
    }

    // 添加客户端
    client.addNameNode("hadoop-master:50005", 2001);
    client.addDataNode("hadoop-slave1:50051", 1001);
    client.addDataNode("hadoop-slave2:50052", 1002);

    cout << "HelloWorld!\n";
    while (true) {
        char *buffer = new char[BUFFER_SIZE];
        handleRequest(serverSocket, buffer);
        delete[] buffer;
    }
}

void
handleRequest(int serverSocket, char *buffer) {
    int socket = accept(serverSocket, NULL, NULL);//监听客户端的请求，没有请求到来的话会一直阻塞
    if (socket == -1) {
        handleError("accept 错误");
    }
    cout << "client发起连接..." << endl;
    getBuffer(socket, buffer);
}

void
handleError(string msg) { //错误处理函数
    cout << msg << endl;
    exit(-1);
}

void
bindToAddress(int serverSocket) { //将socket与某个地址绑定
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;//使用Unix domain
    strncpy(address.sun_path, path.c_str(), sizeof(path));//这个地址的类型有3种，参考上文所说，这里我们使用“系统路径”这一类型
    if (remove(path.c_str()) == -1 && errno != ENOENT) { //绑定之前先要将这个路径对应的文件删除，否则会报EADDRINUSE
        handleError("删除失败");
    }
    if (bind(serverSocket, (struct sockaddr *) &address, sizeof(address)) == -1) {
        handleError("地址绑定失败");
    }
}

void
getBuffer(int socket, char *buffer) {
    int numberOfReaded, numberOfWrited = 0;
//    while (true) {
    memset(buffer, BUFFER_SIZE, '\0');
    numberOfReaded = recv(socket, buffer, BUFFER_SIZE, 0);//读取客户端进程发送的数据
    cout << buffer << endl;
    if (numberOfReaded == -1) {
        handleError("读取数据错误");
    } else if (numberOfReaded == 0) {
        cout << "客户端关闭连接\n";
        close(socket);
        return;
    }
    if (numberOfReaded > 0) {
        buffer[numberOfReaded] = '\0';
        handle(socket, buffer);
        cout << "收到对端进程数据长度为" << numberOfReaded << "开始echo" << endl;
//            numberOfWrited = write(socket, buffer, numberOfReaded);//然后原版返回
//            cout<< "  写入的结果为"<< numberOfWrited<< endl;
    }
//    }
}

void
handle(int socket, const char *buffer) {
    vector<string> components;
    getComponent(buffer, components);
    commands command = getCommand(components[0]);
    string response;
    switch (command) {
        case QUIT:
            break;
        case READ:
            if (components.size() != 3) {
                response = "Parameter Error!";
            } else {
                response = "Read Sucess!";
                client.readFile(components[1], components[2]);
            }
            write(socket, response.c_str(), response.size());
            break;
        case WRITE:
            if (components.size() != 3) {
                response = "Parameter Error!";
            } else {
                response = "Write Sucess!";
                client.addNewFile(components[1], components[2], time(&time1), time(&time1), time(&time1));
            }
            write(socket, response.c_str(), response.size());
            break;
        default:
            break;
    }
}

commands
getCommand(string command) {
    commands o = DEFAULT;
    if (strcmp(command.c_str(), "quit") == 0)
        o = QUIT;
    else if (strcmp(command.c_str(), "send") == 0)
        o = SEND;
    else if (strcmp(command.c_str(), "getattr") == 0)
        o = GETATTR;
    else if (strcmp(command.c_str(), "open") == 0)
        o = OPEN;
    else if (strcmp(command.c_str(), "read") == 0)
        o = READ;
    else if (strcmp(command.c_str(), "write") == 0)
        o = WRITE;
    else if (strcmp(command.c_str(), "release") == 0)
        o = RELEASE;
    else if (strcmp(command.c_str(), "mknod") == 0)
        o = MKNOD;
    else if (strcmp(command.c_str(), "rm") == 0)
        o = RM;
    else if (strcmp(command.c_str(), "mkdir") == 0)
        o = MKDIR;
    else if (strcmp(command.c_str(), "readdir") == 0)
        o = READDIR;
    else if (strcmp(command.c_str(), "rmdir") == 0)
        o = RMDIR;
    return o;
}