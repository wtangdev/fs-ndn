#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>
#include "Client/clientserver.hpp"
#include "fs.hpp"

using  namespace std;

struct msg_st {
    long int msg_type;
    char text[MAX_TEXT];
};

int
main(int argc, char *argv[]) {
    struct msg_st data;
    char buffer[BUFSIZ];
    int msgid = -1;

    //建立消息队列
    msgid = msgget((key_t) 1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    //向消息队列中写消息，直到写入end
    //输入数据
    string command = "";
    for (int i = 1; i < argc; i++) {
        command += string(argv[i]);
        command += " ";
    }
    data.msg_type = 1;    //注意2
    strcpy(data.text, command.c_str());
    //向队列发送数据
    if (msgsnd(msgid, (void *) &data, MAX_TEXT, 0) == -1) {
        fprintf(stderr, "msgsnd failed\n");
        exit(EXIT_FAILURE);
    }
    if(msgrcv(msgid, (void*)&data, BUFSIZ, 1, 0) == -1)
    {
//            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    cout<< data.text<< endl;
    exit(EXIT_SUCCESS);
}
