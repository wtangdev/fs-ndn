//
// Created by anson on 19-2-28.
//

#ifndef FS_NDN_INODEFILE_HPP
#define FS_NDN_INODEFILE_HPP

#include "fileblock.hpp"
#include "inode.hpp"

class INodeFile : public INode
{
  public:
    bool isNULL();
    bool isRoot();
    bool isDirectory();

    long long getSize();

    int write(const char* content, long long size);
    int read(char* buffer, long long size);

    // 虽然感觉此处加快速度对系统整体的性能提升意义不大，但是针对论文的书写，可以加快一下这里的读写。
    // 使用的方法是，每一个节点存储的段都是连续且相等的，所以可以根据数组下标轻松的找到需要的段
    // 在read时只需要进行一下膜运算即可.
    int insertSeg(const char* content, int size, int seg);
    int readSeg(char* buffer, int size, int seg);

    int removeFile();

    INodeFile();
    INodeFile(string name, time_t mtime, time_t atime, time_t ctime);
    INodeFile(INode* other);
    //    ~INodeFile();

  private:
    vector<FileBlock> fileblocks;
    long long size;
};

#endif // FS_NDN_INODEFILE_HPP
