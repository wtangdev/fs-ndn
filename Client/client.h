#ifndef CLIENT_H
#define CLIENT_H

#include "../DataNode/datanodeclient.hpp"
#include "../NameNode/filemeta.hpp"
#include "../NameNode/namenodeclient.hpp"
#include "iostream"
using namespace std;

// Client类是与用户进行直接交互的客户端，其主要负责的功能有：
// 发起文件写请求
// 发起文件读请求
// 文件删除
// 目录删除
// 与DataNode建立连接，断开连接
// 与NameNode建立连接，断开连接
class Client
{
  public:
    Client();

    int addNameNode(string ip, int node_id);
    int removeNameNode(int node_id);

    int addDataNode(string ip, int node_id);
    int removeDataNode(int node_id);

    int addNewFile(string name,
                   const char* content,
                   long long size,
                   time_t mtime,
                   time_t atime,
                   time_t ctime);
    int readFile(string name, char* buffer, long long size);
    int delFIle(string name);
    int delDir(string prefix);

    long long getFileSize(string name);

  private:
    vector<DataNodeClient> data_nodes;
    vector<NameNodeClient> name_nodes;
    void updateNodes();
};

#endif // CLIENT_H
