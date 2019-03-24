#ifndef NAMENODE_HPP
#define NAMENODE_HPP

#include "../DataNode/datanodeclient.hpp"
#include "filemeta.hpp"

class NameNode
{
  public:
    NameNode();

    int addDataNode(string ip, int node_id);
    int removeDataNode(int node_id);

    // 为文件生成命名数据数据信息，并建立写入位置索引,然后返回写入位置索引个客户端
    vector<SegIndex> addNewFile(string name,
                                long long size,
                                time_t mtime,
                                time_t atime,
                                time_t ctime);
    vector<SegIndex> readFile(string name);
    int delFile(string name);
    int delDir(string name);

    int addNewFileToNode(string name,
                         const char* content,
                         long long size,
                         int node_id);

    long long getFileSize(string name);

  private:
    vector<DataNodeClient> data_nodes;
    vector<FileMeta> files;
    void updateNodes();
    bool spaceEnough(long long size);
    vector<FileMeta>::iterator findFile(string name);
};

#endif // NAMENODE_HPP
