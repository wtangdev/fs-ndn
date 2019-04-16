//
// Created by anson on 4/16/19.
//

#ifndef FSNDN_CLIENTSERVER_HPP
#define FSNDN_CLIENTSERVER_HPP

#include "../fs.hpp"

#define BACK_LOG 1000
#define BUFFER_SIZE 2048
std::string path = "./namo_amitabha";

const int fsndn::seg_size = 1048576; //

enum commands{
    QUIT, SEND, DEFAULT, GETATTR, OPEN, READ, WRITE, RELEASE,  MKNOD, RM, MKDIR, RMDIR, READDIR
};

commands
getCommand(std::string command);

void
handleError(std::string msg); //错误处理函数

void
bindToAddress(int serverSocket); //将socket与某个地址绑定

void
getBuffer(int socket, char * buffer);

// 需要根据收到了指令来联系 NameNode 和 DataNode
void
handle(int socket, const char *buffer);

void
handleRequest(int serverSocket, char * buffer);



inline void
getComponent(const char * buffer ,std::vector<std::string> &components) {
    std::string buff = std::string(buffer);
    size_t first_comp_pos = buff.find(' ');
    while(first_comp_pos != std::string::npos) {
        if (first_comp_pos != 0)
            components.push_back(buff.substr(0, first_comp_pos));
        buff = buff.substr(first_comp_pos+1);
        first_comp_pos = buff.find(' ');
    }
//    components.push_back(buff.substr(0, first_comp_pos));
    return;
}

#endif //FSNDN_CLIENTSERVER_HPP
