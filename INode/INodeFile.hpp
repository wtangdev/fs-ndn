//
// Created by anson on 19-2-28.
//

#ifndef FS_NDN_INODEFILE_HPP
#define FS_NDN_INODEFILE_HPP

#include "inode.hpp"

// 这里的INodeFile存储文件的方法调用系统的read和write，存在本地的文件系统中。
class INodeFile : public INode{
public:
    bool isNULL();
    bool isRoot();
    bool isDirectory();

    int fileRead();

    string getPath();

    INodeFile();
    INodeFile(string name, time_t mtime, time_t atime, time_t ctime);
    INodeFile(INodeFile * other);
//    ~INodeFile();

private:
    string filepath; // 文件在系统中的实际路径
};


#endif //FS_NDN_INODEFILE_HPP
