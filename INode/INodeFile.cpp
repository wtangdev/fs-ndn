//
// Created by anson on 19-2-28.
//

#include "INodeFile.hpp"
#include "../fs.hpp"

using namespace std;

INodeFile::INodeFile() : INode(){}

INodeFile::INodeFile(string name, time_t mtime, time_t atime, time_t ctime) : INode(name, mtime, atime, ctime){
    // 获取文件路径
    string pathname = fsndn::root_path;
    pathname.append(name);
    this->filepath = pathname;
}

INodeFile::INodeFile(INodeFile *other) : INode(other){
    this->filepath = other->filepath;
}

bool INodeFile::isNULL() {
    return false;
}

bool INodeFile::isDirectory() {
    return false;
}

bool INodeFile::isRoot() {
    return false;
}

string INodeFile::getPath() {
    return this->filepath;
}

int INodeFile::fileRead() {
//    fread()
}