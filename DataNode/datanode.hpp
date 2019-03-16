//
// Created by Anson on 2019-03-03.
//

#ifndef FS_NDN_NAMENODE_HPP
#define FS_NDN_NAMENODE_HPP

#include "../INode/inodefile.hpp"


class NameNode{
public:
    NameNode();
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

protected:

private:
    vector<INodeFile> names;    // 当前节点管理的所有文件
};


#endif //FS_NDN_NAMENODE_HPP
