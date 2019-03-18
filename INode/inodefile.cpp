//
// Created by anson on 19-2-28.
//

#include "inodefile.hpp"
#include "../fs.hpp"
#include "inodedirectory.hpp"
#include "../logger.hpp"

using namespace std;

INodeFile::INodeFile() : INode(){}

/*
 * 此处使用了INodeDirectory
INodeFile::INodeFile(string name, time_t mtime, time_t atime, time_t ctime) : INode(name, mtime, atime, ctime){

    // 根据路径创建相应的目录以满足结构化访问
    vector<string> components;
    split_all_component(name, components);
    INodeDirectory * curnode = &fsndn::root;
    // 第一个节点是"/"， 最后一个节点应该是this
    components[0] = "";
    for (size_t i = 1; i < components.size()-1; i++) {
        INodeDirectory * tempnode = (INodeDirectory *) curnode->getNodeLink(components[i]);
        if (!tempnode == NULL) {
            curnode = tempnode;
            break;
        }
//        delete(tempnode);
        components[0].append("/");
        components[0].append(components[i]);
        tempnode = new INodeDirectory(components[0], mtime, atime, ctime);
        curnode->addChild(tempnode);
        tempnode->parent = curnode;
        curnode = tempnode;
    }
    curnode->addChild(this);
    this->parent = curnode;
}
 */

INodeFile::INodeFile(string name, time_t mtime, time_t atime, time_t ctime) : INode(name, mtime, atime, ctime){
    this->size = 0;
}

INodeFile::INodeFile(INodeFile *other) : INode(other){
    //    this->filepath = other->filepath;
}

long long INodeFile::getSize() {
    return this->size;
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

int INodeFile::write(const char * content, long long size){
    this->size = size;
    int seg_size = fsndn::seg_size;
    if (size <= seg_size) {
        FileBlock fileBlock(this->getNdnPath(), content, size, 0);
        fileblocks.push_back(fileBlock);
    } else {
        char temp_content[seg_size];
        int seg = 0;
        // 将前n*seg_size存进去直到最后不满一个seg
        while ((seg+1) * seg_size < size) {
            memset(temp_content, 0, seg_size);
            memmove(temp_content, content+(seg*seg_size), seg_size);
            FileBlock fileBlock(this->getNdnPath(), temp_content, seg_size, seg);
            fileblocks.push_back(fileBlock);
            seg++;
        }
        // 把最后一点放进去
        memset(temp_content, 0, seg_size);
        memmove(temp_content, content+(seg*seg_size), size-(seg*seg_size));
        FileBlock fileBlock(this->getNdnPath(), temp_content, size-(seg*seg_size), seg);
        fileblocks.push_back(fileBlock);
    }
    return 0;
}

int INodeFile::read(char *buffer, long long size) {
    int seg_size = fsndn::seg_size;
//    FILE_LOG(LOG_DEBUG)<< "segs = " << fileblocks.size()<< endl;
    for (auto item : fileblocks) {
        int temp_seg = item.getSeg();
//        FILE_LOG(LOG_DEBUG)<< "seg = " << temp_seg<< endl;
        int temp_size = item.getSize();
        char temp_content[temp_size];
        item.read(temp_content, temp_size);
        memmove(buffer+seg_size * temp_seg, temp_content, temp_size);
    }
    return 0;
}

int INodeFile::insertSeg(const char *content, int size, int seg) {
    if (size > fsndn::seg_size) {
        FILE_LOG(LOG_ERROR)<< "Insert Seg error, content size is bigger than seg size!"<< endl;
        return -1;
    }
    this->size += size;
    FileBlock fileBlock(this->getNdnPath(), content, size, seg);
    fileblocks.push_back(fileBlock);
    return 0;
}

int INodeFile::readSeg(char *buffer, int size, int seg) {
    if (size > fsndn::seg_size) {
        FILE_LOG(LOG_ERROR)<< "Get Seg error, buffer size is bigger than ndn seg size!"<< endl;
        return -1;
    }
    for (auto item : fileblocks) {
        if (item.getSeg() == seg) {
            int seg_size = item.getSize();
            if (seg_size > size) {
                FILE_LOG(LOG_ERROR)<< "Get Seg error, buffer size is smaller than seg size!"<< endl;
                return -2;
            }
            char temp_content[seg_size];
            item.read(temp_content, seg_size);
            memmove(buffer, temp_content, size);
            break;
        }
    }
    return 0;
}

int INodeFile::removeFile()
{
   FILE_LOG(LOG_DEBUG) << "removeFile need to be implmented"<< endl;
   return -1;
}
