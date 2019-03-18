#include "filemeta.hpp"
#include "iostream"
#include "../logger.hpp"
using namespace std;

FileMeta::FileMeta(string name, int segs, int size)
{
    this->name = ndn::Name(name);
    this->segs = segs;
    this->size = size;
    this->read_times = 0;
}

ndn::Name FileMeta::getName()
{
    return this->name;
}

int FileMeta::getSegs()
{
    return this->segs;
}

long long FileMeta::getSize()
{
    return this->size;
}

int FileMeta::getReadTimes()
{
    return read_times;
}

set<int> FileMeta::getUseNodes()
{
    return this->use_nodes;
}

int FileMeta::setSegs(int segs)
{
    this->segs = segs;
    return 0;
}

int FileMeta::addReadTimes()
{
    this->read_times++;
    return 0;
}

int FileMeta::addUseNodes(int node)
{
    this->use_nodes.insert(node);
    return 0;
}

int FileMeta::minusReadTimes()
{
    this->read_times--;
    return 0;
}

int FileMeta::minusUseNodes(int node)
{
    set<int>::iterator it = find(this->use_nodes.begin(), this->use_nodes.end(),
                                    node);
    if (it == use_nodes.end()) {
        FILE_LOG(LOG_ERROR)<< "Minus Use Nodes error, "<< this->name.toUri()<<" has no segment in node "<< node<< endl;
        return -1;
    }
    this->use_nodes.erase(it);
    return 0;
}

bool FileMeta::operator== (const string &other_file_name) const
{
    return this->name.toUri() == other_file_name;
}
