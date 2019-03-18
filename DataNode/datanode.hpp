//
// Created by Anson on 2019-03-03.
//

#ifndef FS_NDN_DATANODE_HPP
#define FS_NDN_DATANODE_HPP

#include "../INode/inodefile.hpp"


class DataNode{
public:
    explicit DataNode(long long node_size);
    // 创建空文件
    int addEmptyFile(string name, time_t mtime, time_t atime, time_t ctime);
    // 创建含内容的文件
    int addNewFile(string name, const char * content, long long size, time_t mtime, time_t atime, time_t ctime);
    int delFile(string name);
    int delDir(string prefix);

    long long getFileSize(string name);

    int writeToFile(string name, const char * content, long long size);
    int readFromFile(string name, char * buffer, long long size);

    int addFileSeg(string name, const char * content, int size, int seg);
    int getFileSeg(string name, char * buffer, int size, int seg);

    vector<string> showChildren(string prefix);
    vector<string> showAllChildren();

    long long getNodeSize();
    long long getSpaceSize();

protected:

private:
    vector<INodeFile> names;    // 当前节点管理的所有文件
    long long node_size;
    long long used_size;
};


#endif //FS_NDN_DATANODE_HPP
