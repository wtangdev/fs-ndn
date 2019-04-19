//
// Created by anson on 19-2-28.
//

#include "inodefile.hpp"
#include "../fs.hpp"
#include "../logger.hpp"
#include "inodedirectory.hpp"

using namespace std;

INodeFile::INodeFile()
        : INode() {}

/*
 * 此处使用了INodeDirectory
INodeFile::INodeFile(string name, time_t mtime, time_t atime, time_t ctime) :
INode(name, mtime, atime, ctime){

    // 根据路径创建相应的目录以满足结构化访问
    vector<string> components;
    split_all_component(name, components);
    INodeDirectory * curnode = &fsndn::root;
    // 第一个节点是"/"， 最后一个节点应该是this
    components[0] = "";
    for (size_t i = 1; i < components.size()-1; i++) {
        INodeDirectory * tempnode = (INodeDirectory *)
curnode->getNodeLink(components[i]); if (!tempnode == NULL) { curnode =
tempnode; break;
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

INodeFile::INodeFile(string name, time_t mtime, time_t atime, time_t ctime)
        : INode(name, mtime, atime, ctime) {
    this->size = 0;
}

INodeFile::INodeFile(INode *other)
        : INode(other) {
    //    this->filepath = other->filepath;
    this->size = INodeFile(other).size;
    this->fileblocks = INodeFile(other).fileblocks;
}

long long
INodeFile::getSize() {
    return this->size;
}

bool
INodeFile::isNULL() {
    return false;
}

bool
INodeFile::isDirectory() {
    return false;
}

bool
INodeFile::isRoot() {
    return false;
}

int
INodeFile::write(const char *content, long long size) {
    this->size = size;
    int seg_size = fsndn::seg_size;
    if (size <= seg_size) {
        FileBlock fileBlock(this->getNdnPath(), content, size, 0);
        fileblocks.push_back(fileBlock);
    } else {
        //        char temp_content[seg_size];
        char *temp_content = new char[seg_size];
        int seg = 0;
        // 将前n*seg_size存进去直到最后不满一个seg
        while ((seg + 1) * seg_size < size) {
            memset(temp_content, 0, seg_size);
            memmove(temp_content, content + (seg * seg_size), seg_size);
            FileBlock fileBlock(
                    this->getNdnPath(), temp_content, seg_size, seg);
            fileblocks.push_back(fileBlock);
            seg++;
        }
        // 把最后一点放进去
        memset(temp_content, 0, seg_size);
        memmove(
                temp_content, content + (seg * seg_size), size - (seg * seg_size));
        FileBlock fileBlock(
                this->getNdnPath(), temp_content, size - (seg * seg_size), seg);
        delete[] temp_content;
        fileblocks.push_back(fileBlock);
    }
    return 0;
}

int
INodeFile::read(char *buffer, long long size) {
    int seg_size = fsndn::seg_size;
    //    FILE_LOG(LOG_DEBUG)<< "segs = " << fileblocks.size()<< endl;
    for (auto item : fileblocks) {
        int temp_seg = item.getSeg();
        //        FILE_LOG(LOG_DEBUG)<< "seg = " << temp_seg<< endl;
        int temp_size = item.getSize();
        //        char temp_content[temp_size];
        char *temp_content = new char[temp_size];
        item.read(temp_content, temp_size);
        memmove(buffer + seg_size * temp_seg, temp_content, temp_size);
        delete[] temp_content;
    }
    return 0;
}

int
INodeFile::insertSeg(const char *content, int size, int seg) {
    if (size > fsndn::seg_size) {
        FILE_LOG(LOG_ERROR)
            << "Insert Seg error, content size is bigger than seg size!" << endl;
        return -1;
    }
    this->size += size;
    FileBlock fileBlock(this->getNdnPath(), content, size, seg);
    fileblocks.push_back(fileBlock);
    return 0;
}

int
INodeFile::readSeg(char *buffer, int size, int seg) {
    if (size > fsndn::seg_size) {
        FILE_LOG(LOG_ERROR)
            << "Get Seg error, buffer size is bigger than ndn seg size!" << endl;
        return -1;
    }
    // TODO: 此处可以通过二分查找来提高速度
    // 虽然感觉此处加快速度对系统整体的性能提升意义不大，但是针对论文的书写，可以加快一下这里的读写。
//    char *temp_content = new char[size];
    this->fileblocks[seg % this->fileblocks.size()].read(buffer, size);
//    memmove(buffer, temp_content, size);
//    delete[] temp_content;
    /*
    for (auto item : fileblocks) {
        if (item.getSeg() == seg) {
            //            int seg_size = item.getSize();
            //            if (seg_size > size) {
            //                FILE_LOG(LOG_ERROR)<< "Get Seg error, buffer size
            //                is smaller than seg size!"<< endl; return -2;
            //            }
            //            char temp_content[size];
            char *temp_content = new char[size];
            item.read(temp_content, size);
            memmove(buffer, temp_content, size);
            delete[] temp_content;
            break;
        }
    }
     */
    return 0;
}

int
INodeFile::removeFile() {
    FILE_LOG(LOG_DEBUG) << "removeFile need to be implmented" << endl;
    return -1;
}
