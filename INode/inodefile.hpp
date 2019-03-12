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

    int getSize();
    
    int write(unsigned char * content, int size);
    int read(unsigned char * buffer, int size);


    INodeFile();
    INodeFile(string name, time_t mtime, time_t atime, time_t ctime);
    INodeFile(INodeFile * other);
//    ~INodeFile();

private:
    vector<FileBlock> fileblocks;
    int size;
};


#endif //FS_NDN_INODEFILE_HPP
