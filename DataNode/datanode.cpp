//
// Created by Anson on 2019-03-03.
//

#include "datanode.hpp"
#include "../logger.hpp"
#include "../fs.hpp"

vector<INodeFile>::iterator findFile(vector<INodeFile> &files, string name)
{
    FILE_LOG(LOG_DEBUG) << "FINDFILE NEED TO BE IMPLEMENTED!\n";
    vector<INodeFile>::iterator it;
    it = find(files.begin(), files.end(), name);
    return it;
}

NameNode::NameNode()
{
    time_t time1;
    INodeFile rootnode("", time(&time1), time(&time1), time(&time1));
    this->names.push_back(rootnode);
}

int NameNode::addEmptyFile(string name, time_t mtime, time_t atime, time_t ctime)
{
    vector<INodeFile>::iterator it = findFile(this->names, name);
    if (it != this->names.end())
    {
        FILE_LOG(LOG_ERROR) << "FSNDN already have file named " << name << endl;
        return -1;
    }
    INodeFile new_file(name, mtime, atime, ctime);
    this->names.push_back(new_file);
    FILE_LOG(LOG_DEBUG) << "You insert an empty file\n";
    return 0;
}

int NameNode::addNewFile(string name, unsigned char *content, int size, time_t mtime, time_t atime, time_t ctime)
{
    vector<INodeFile>::iterator it = findFile(this->names, name);
    if (it != this->names.end())
    {
        FILE_LOG(LOG_ERROR) << "FSNDN already have file named " << name << endl;
        return -1;
    }
    INodeFile new_file(name, mtime, atime, ctime);
    new_file.write(content, size);
    this->names.push_back(new_file);
    return 0;
}

int NameNode::delFile(string name)
{
    vector<INodeFile>::iterator it = findFile(this->names, name);
    if (it == this->names.end())
    {
        FILE_LOG(LOG_ERROR) << "FSNDN already have file named " << name << endl;
        return -1;
    }
    this->names.erase(it);
    return 0;
}

int NameNode::delDir(string prefix) {
    FILE_LOG(LOG_DEBUG)<< "Delete Directory need to be implemented!\n";
    return -1;
}

int NameNode::getFileSize(string name)
{
    vector<INodeFile>::iterator it = findFile(this->names, name);
    if (it == this->names.end())
    {
        FILE_LOG(LOG_ERROR) << "FSNDN have no file named " << name << endl;
        return -1;
    }
    return (*it).getSize();
}

int NameNode::writeToFile(string name, unsigned char *content, int size)
{
    vector<INodeFile>::iterator it = findFile(this->names, name);
    if (it == this->names.end())
    {
        FILE_LOG(LOG_ERROR) << "FSNDN have no file named " << name << endl;
        return -1;
    }
    (*it).write(content, size);
    return 0;
}

int NameNode::readFromFile(string name, unsigned char *buffer, int size)
{
    vector<INodeFile>::iterator it = findFile(this->names, name);
    if (it == this->names.end())
    {
        FILE_LOG(LOG_ERROR) << "FSNDN have no file named " << name << endl;
        return -1;
    }
    (*it).read(buffer, size);
    return 0;
}

vector<string> NameNode::showChildren(string prefix)
{
    vector<string> children_name;
    ndn::Name prefix_name(prefix);
    for (auto temp : this->names)
    {
        if (prefix_name.isPrefixOf(temp.getNdnName()))
        {
            ndn::Name child_name = temp.getNdnName().getSubName(prefix_name.getComponentCount());
            if (child_name.getComponentCount() > 0)
                children_name.push_back(child_name.getComponent(0).getValue().toRawStr());
        }
    }
    return children_name;
}
