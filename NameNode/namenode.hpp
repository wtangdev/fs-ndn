#ifndef NAMENODE_HPP
#define NAMENODE_HPP

#include "../DataNode/datanode_client.hpp"
#include "filemeta.hpp"

class NameNode
{
public:
    NameNode();

    int addDataNode(string ip, int node_id);
    int removeDataNode(int node_id);

    int addNewFile(string name, const char * content, long long size);
    int readFile(string name, char * buffer, long long size);
    int delFile(string name);

    int addNewFileToNode(string name, const char * content, long long size, int node_id);

    long long getFileSize(string name);

private:
    vector<DataNodeClient> nodes;
    vector<FileMeta> files;
    void updateNodes();
    bool spaceEnough(long long size);
    vector<FileMeta>::iterator findFile(string name);
};

#endif // NAMENODE_HPP
