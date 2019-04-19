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

    // 不建议使用,因为很难能把一个大文件完整的存放到内存里面去
    int addNewFile(string name,
                   const char *content,
                   long long size,
                   time_t mtime,
                   time_t atime,
                   time_t ctime);

    // 不建议使用,因为很难能把一个大文件完整的存放到内存里面去
    int readFile(string name, char *buffer, long long size);

    // 重载这个函数的意义是因为，在文件大小非常大的情况下，是不能把所有文件数据写入内存的，应当一点一点的读写
    int addNewFile(
      string name, string file_path, time_t mtime, time_t atime, time_t ctime);

    // 同样的，对于大文件，写也要一块一块的写
    int readFile(string name, string file_path);

    int addNewFileSign(
      string name, string file_path, time_t mtime, time_t atime, time_t ctime);

    // 同样的，对于大文件，写也要一块一块的写
    int readFileSign(string name, string file_path);

    int delFIle(string name);

    int delDir(string prefix);

    long long getFileSize(string name);

    void quitDatanode();
    void quitNamenode();

    bool static checkSignautre(string name, const char * context, int size, const char * signautre);

  private:
    vector<DataNodeClient> data_nodes;
    vector<NameNodeClient> name_nodes;

    void updateNodes();
};

#endif // CLIENT_H
