//
// Created by Anson on 2019-03-09.
//

#ifndef FS_NDN_FILEBLOCK_HPP
#define FS_NDN_FILEBLOCK_HPP

#include "iostream"
using namespace std;

class SFileTable {
public:
    SFileTable(string pathstr, int offset);

    string getPath();
    int getSpace();
    int getOffset();
    void setOffset(int ofs);

    bool operator<(const SFileTable & otherfile) const;
    bool operator==(const SFileTable & otherfile) const;


private:
    string path;
    int offset;
    int space;
};

// FileBlock负责文件的实际存储，其是文件存储的最小单位，无需负责大文件分段和小文件聚合的具体实现
//
class FileBlock {
public:
    static vector<SFileTable> space_path;

    FileBlock(string name, unsigned char * data, int size ,int seg);
    FileBlock(FileBlock * other);

    int getSeg();
    int getSize();

    int read(unsigned char * buffer, int size);
    int write(unsigned char * content, int size);
    vector<SFileTable> getSpaceTable();
    static void updateSpaceTable(string path, int size);

    bool operator<(const FileBlock & otherfile) const;
private:
    string path;
    string name;    // 文件名，用来生成唯一的路径
    int size;
    int offset;
    int seg;    // 文件的第几段

};



#endif //FS_NDN_FILEBLOCK_HPP
