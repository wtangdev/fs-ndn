//
// Created by Anson on 2019-03-03.
//

#include "datanode.hpp"
#include "../fs.hpp"
#include "../logger.hpp"

int
  DataNode::findFile(string name, INodeFile &file)
{
    //    FILE_LOG(LOG_DEBUG) << "FINDFILE NEED TO BE IMPLEMENTED!\n";
    unordered_map<string, INodeFile>::iterator it;
    it = this->names.find(name);
    if (it == this->names.end()) {
        return -1;
    }
    file = it->second;
    return 0;
}

DataNode::DataNode(long long node_size)
{
    time_t time1;
    INodeFile rootnode("", time(&time1), time(&time1), time(&time1));
    this->names.insert(
      unordered_map<string, INodeFile>::value_type("", rootnode));
    this->node_size = node_size;
    this->used_size = 0;
}

int
  DataNode::addEmptyFile(string name, time_t mtime, time_t atime, time_t ctime)
{
    // 此处应该相信 NameNode
    // 的管理能力，不会存储重复的文件进去的，所以可以去掉该判断
    //    vector<INodeFile>::iterator it = findFile(this->names, name);
    //    if (it != this->names.end()) {
    //        FILE_LOG(LOG_ERROR) << "FSNDN already has file named " << name <<
    //        endl; return -1;
    //    }
    INodeFile new_file(name, mtime, atime, ctime);
    this->names.insert(
      unordered_map<string, INodeFile>::value_type(name, new_file));
    FILE_LOG(LOG_DEBUG) << "You insert an empty file\n";
    return this->names.size() - 1;
}

int
  DataNode::addNewFile(string name,
                       const char *content,
                       long long size,
                       time_t mtime,
                       time_t atime,
                       time_t ctime)
{
    // 此处应该相信 NameNode
    // 的管理能力，不会存储重复的文件进去的，所以可以去掉该判断
    //    vector<INodeFile>::iterator it = findFile(this->names, name);
    //    if (it != this->names.end()) {
    //        FILE_LOG(LOG_ERROR) << "FSNDN already has file named " << name <<
    //        endl; return -1;
    //    }
    INodeFile new_file(name, mtime, atime, ctime);
    new_file.write(content, size);
    this->names.insert(
      unordered_map<string, INodeFile>::value_type(name, new_file));
    this->used_size += size;
    return this->names.size() - 1;
}

int
  DataNode::delFile(string name)
{
    unordered_map<string, INodeFile>::iterator it = this->names.find(name);
    if (it == this->names.end()) {
        FILE_LOG(LOG_ERROR) << "FSNDN has no file named " << name << endl;
        return -1;
    }
    INodeFile inode_file = it->second;
    this->used_size -= inode_file.getSize();
    inode_file.removeFile();
    this->names.erase(it);
    return 0;
}

int
  DataNode::delDir(string prefix)
{
    FILE_LOG(LOG_DEBUG) << "Delete Directory need to be implemented!\n";
    return -1;
}

long long
  DataNode::getFileSize(string name)
{
    INodeFile inode_file;
    if (this->findFile(name, inode_file) == -1) {
        FILE_LOG(LOG_ERROR) << "FSNDN has no file named " << name << endl;
        return -1;
    }
    return inode_file.getSize();
}

int
  DataNode::writeToFile(string name, const char *content, long long size)
{
    // 相信 NameNode
    //    vector<INodeFile>::iterator it = findFile(this->names, name);
    //    if (it == this->names.end()) {
    //        FILE_LOG(LOG_ERROR) << "FSNDN has no file named " << name << endl;
    //        return -1;
    //    }
    INodeFile inode_file;
    this->findFile(name, inode_file);
    inode_file.write(content, size);
    this->used_size += size;
    return 0;
}

int
  DataNode::readFromFile(string name, char *buffer, long long size)
{
    //    vector<INodeFile>::iterator it = findFile(this->names, name);
    //    if (it == this->names.end()) {
    //        FILE_LOG(LOG_ERROR) << "FSNDN has no file named " << name << endl;
    //        return -1;
    //    }
    INodeFile inode_file;
    this->findFile(name, inode_file);
    inode_file.read(buffer, size);
    return 0;
}

int
  DataNode::addFileSeg(string name, const char *content, int size, int seg)
{
    INodeFile inode_file;
    if (this->findFile(name, inode_file) == -1) {
        FILE_LOG(LOG_DEBUG)
          << "FSNDN has no file named " << name << ", So Create it" << endl;
        time_t time1;
        this->addEmptyFile(name, time(&time1), time(&time1), time(&time1));
        inode_file = this->names.find(name)->second;
        //        return -1;
    }
    inode_file.insertSeg(content, size, seg);
    this->used_size += size;
    return 0;
}

int
  DataNode::getFileSeg(string name, char *buffer, int size, int seg)
{
    INodeFile inode_file;
    if (this->findFile(name, inode_file) == -1) {
        FILE_LOG(LOG_ERROR) << "FSNDN has no file named" << name << endl;
        return -1;
    }
    cout << inode_file.getSize() << endl;
    inode_file.readSeg(buffer, size, seg);
    return 0;
}

vector<string>
  DataNode::showChildren(string prefix)
{
    FILE_LOG(LOG_DEBUG) << "YOU WILL NERVER USE THIS FUNCTION" << endl;
    vector<string> children_name;

    /*
    ndn::Name prefix_name(prefix);
    for (auto temp : this->names) {
        if (prefix_name.isPrefixOf(temp.getNdnName())) {
            //            ndn::Name child_name =
            // temp.getNdnName().getSubName(prefix_name.getComponentCount());
            // ndn-cpp 建议使用size()替代getComponentCount()
            ndn::Name child_name =
              temp.getNdnName().getSubName(prefix_name.size());
            if (child_name.size() > 0)
                children_name.push_back(
                  child_name.get(0).getValue().toRawStr());
        }
    }
    */

    return children_name;
}

vector<string>
  DataNode::showAllChildren()
{

    FILE_LOG(LOG_DEBUG) << "YOU WILL NERVER USE THIS FUNCTION" << endl;
    vector<string> children_name;

    /*
    for (auto temp : this->names) {
        children_name.push_back(temp.getNdnName().toUri());
    }
    */

    return children_name;
}

long long
  DataNode::getNodeSize()
{
    return this->node_size;
}

long long
  DataNode::getSpaceSize()
{
    return this->node_size - this->used_size;
}
