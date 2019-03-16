//
// Created by Anson on 2019-03-03.
//

#ifndef FS_NDN_DATANODE_HPP
#define FS_NDN_DATANODE_HPP

#include "../INode/inodefile.hpp"


class DataNode{
public:
    DataNode();
    // 创建空文件
    int addEmptyFile(string name, time_t mtime, time_t atime, time_t ctime);
    // 创建含内容的文件
    int addNewFile(string name, unsigned char * content, int size, time_t mtime, time_t atime, time_t ctime);
    int delFile(string name);
    int delDir(string prefix);

    int getFileSize(string name);

    int writeToFile(string name, unsigned char * content, int size);
    int readFromFile(string name, unsigned char * buffer, int size);
    vector<string> showChildren(string prefix);
    vector<string> showAllChildren();

protected:

private:
    vector<INodeFile> names;    // 当前节点管理的所有文件
};


#endif //FS_NDN_DATANODE_HPP
