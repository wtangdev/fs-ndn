//
// Created by anson on 19-2-28.
//

#ifndef FS_NDN_INODEFILE_HPP
#define FS_NDN_INODEFILE_HPP

#include "inode.hpp"
#include "fileblock.hpp"

class INodeFile : public INode{
public:
    bool isNULL();
    bool isRoot();
    bool isDirectory();

    long long getSize();
    
    int write(const char * content, long long size);
    int read(char * buffer, long long size);

    int insertSeg(const char * content, int size, int seg);
    int readSeg(char * buffer, int size, int seg);

    int removeFile();

    INodeFile();
    INodeFile(string name, time_t mtime, time_t atime, time_t ctime);
    INodeFile(INodeFile * other);
//    ~INodeFile();

private:
    vector<FileBlock> fileblocks;
    long long size;
};


#endif //FS_NDN_INODEFILE_HPP
