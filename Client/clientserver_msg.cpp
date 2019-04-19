#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include "clientserver.hpp"
#include "../fs.hpp"
#include "client.h"

using namespace std;


struct msg_st
{
    long int msg_type;
    char text[MAX_TEXT];
};

Client client;
time_t time1;

int main()
{
    client.addNameNode("hadoop-master:50005", 2001);
    client.addDataNode("hadoop-slave1:50051", 1001);
    client.addDataNode("hadoop-slave2:50052", 1002);

    int running = 1;
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0; //注意1

    //建立消息队列
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if(msgid == -1)
    {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    //从队列中获取消息，直到遇到end消息为止
    while(running)
    {
        if(msgrcv(msgid, (void*)&data, MAX_TEXT, msgtype, 0) == -1)
        {
//            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        handle(msgid, data.text);
        //遇到end结束
    }
    //删除消息队列

}

void
handle(int msgid, const char *buffer) {
    vector<string> components;
    getComponent(buffer, components);
    commands command = getCommand(components[0]);
    string response;
    msg_st reply;
    switch (command) {
        case QUIT:
            deleteMsg(msgid);
            break;
        case READ:
            if (components.size() != 3) {
                response = "Parameter Error!";
            } else {
                response = "Read Sucess!";
                client.readFile(components[1], components[2]);
            }
            strcpy(reply.text, response.c_str());
            reply.msg_type = 1;
            msgsnd(msgid, (void *)&reply, 30, 0);
            break;
        case WRITE:
            if (components.size() != 3) {
                response = "Parameter Error!";
            } else {
                response = "Write Sucess!";
                client.addNewFile(components[1], components[2], time(&time1), time(&time1), time(&time1));
            }
            strcpy(reply.text, response.c_str());
            reply.msg_type = 1;
            msgsnd(msgid, (void *)&reply, 30, 0);
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

void
deleteMsg(int msgid) {
    if(msgctl(msgid, IPC_RMID, 0) == -1)
    {
//        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}